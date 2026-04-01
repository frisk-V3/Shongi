#include "position.h"
#include "move.h"
#include <cassert>

Position::Position() {
    board.fill(Piece::Empty);
    side = Color::Black;

    set_piece(4, 8, Piece::BKing);
    set_piece(4, 0, Piece::WKing);

    for (int f = 0; f < 9; ++f) {
        set_piece(f, 6, Piece::BPawn);
        set_piece(f, 2, Piece::WPawn);
    }
}

Piece Position::piece_at(int file, int rank) const {
    assert(file >= 0 && file < 9);
    assert(rank >= 0 && rank < 9);
    return board[rank * 9 + file];
}

void Position::set_piece(int file, int rank, Piece p) {
    assert(file >= 0 && file < 9);
    assert(rank >= 0 && rank < 9);
    board[rank * 9 + file] = p;
}

const Hand& Position::hand(Color c) const {
    return (c == Color::Black) ? blackHand : whiteHand;
}

Hand& Position::hand(Color c) {
    return (c == Color::Black) ? blackHand : whiteHand;
}

std::vector<Move> Position::generate_legal_moves() const {
    std::vector<Move> moves;

    // 超簡略：歩と玉だけの動き
    int dir = (side == Color::Black) ? -1 : 1;

    for (int r = 0; r < 9; ++r) {
        for (int f = 0; f < 9; ++f) {
            Piece p = piece_at(f, r);
            if (p == Piece::Empty) continue;

            bool isBlack = (static_cast<int>(p) >= static_cast<int>(Piece::BPawn) &&
                            static_cast<int>(p) <= static_cast<int>(Piece::BKing));
            Color pc = isBlack ? Color::Black : Color::White;
            if (pc != side) continue;

            // 歩
            if (p == Piece::BPawn || p == Piece::WPawn) {
                int nr = r + dir;
                if (nr >= 0 && nr < 9) {
                    Piece target = piece_at(f, nr);
                    if (target == Piece::Empty ||
                        (pc == Color::Black && static_cast<int>(target) >= static_cast<int>(Piece::WPawn)) ||
                        (pc == Color::White && static_cast<int>(target) >= static_cast<int>(Piece::BPawn) &&
                         static_cast<int>(target) <= static_cast<int>(Piece::BKing))) {
                        moves.emplace_back(f, r, f, nr, false, false);
                    }
                }
            }

            // 玉（上下左右＋斜め）
            if (p == Piece::BKing || p == Piece::WKing) {
                static const int df[8] = {1,1,0,-1,-1,-1,0,1};
                static const int dr[8] = {0,-1,-1,-1,0,1,1,1};
                for (int i = 0; i < 8; ++i) {
                    int nf = f + df[i];
                    int nr = r + dr[i];
                    if (nf < 0 || nf >= 9 || nr < 0 || nr >= 9) continue;
                    Piece target = piece_at(nf, nr);
                    if (target == Piece::Empty ||
                        (pc == Color::Black && static_cast<int>(target) >= static_cast<int>(Piece::WPawn)) ||
                        (pc == Color::White && static_cast<int>(target) >= static_cast<int>(Piece::BPawn) &&
                         static_cast<int>(target) <= static_cast<int>(Piece::BKing))) {
                        moves.emplace_back(f, r, nf, nr, false, false);
                    }
                }
            }
        }
    }

    return moves;
}

void Position::make_move(const Move& m) {
    Piece fromP = piece_at(m.fromFile, m.fromRank);
    Piece toP   = piece_at(m.toFile, m.toRank);

    // 簡略：成り・打ちは未実装
    set_piece(m.fromFile, m.fromRank, Piece::Empty);
    set_piece(m.toFile, m.toRank, fromP);

    // 持ち駒処理も本気ならやる（ここでは省略）

    side = (side == Color::Black) ? Color::White : Color::Black;
}

void Position::undo_move(const Move& m, Piece captured, Hand prevBlack, Hand prevWhite, Color prevSide) {
    Piece moved = piece_at(m.toFile, m.toRank);
    set_piece(m.toFile, m.toRank, captured);
    set_piece(m.fromFile, m.fromRank, moved);
    blackHand = prevBlack;
    whiteHand = prevWhite;
    side = prevSide;
}
