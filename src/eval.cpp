#include "eval.h"

int evaluate(const Position& pos, const EvalWeights& w) {
    int score = 0;

    for (int r = 0; r < 9; ++r) {
        for (int f = 0; f < 9; ++f) {
            Piece p = pos.piece_at(f, r);
            switch (p) {
            case Piece::BPawn: score += w.pawnValue; break;
            case Piece::WPawn: score -= w.pawnValue; break;
            case Piece::BKing: score += 10000; break;
            case Piece::WKing: score -= 10000; break;
            default: break;
            }
        }
    }

    return (pos.side_to_move() == Color::Black) ? score : -score;
}
