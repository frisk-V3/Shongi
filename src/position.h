#pragma once
#include <array>
#include <vector>
#include <cstdint>

enum class Color : int {
    Black = 0,
    White = 1
};

enum class Piece : int {
    Empty = 0,
    // 先手駒
    BPawn, BLance, BKnight, BSilver, BGold, BBishop, BRook, BKing,
    // 後手駒
    WPawn, WLance, WKnight, WSilver, WGold, WBishop, WRook, WKing
};

struct Hand {
    int pawn = 0;
    int lance = 0;
    int knight = 0;
    int silver = 0;
    int gold = 0;
    int bishop = 0;
    int rook = 0;
};

class Move;

class Position {
public:
    Position();

    Piece piece_at(int file, int rank) const; // file: 0-8, rank: 0-8
    void set_piece(int file, int rank, Piece p);

    Color side_to_move() const { return side; }
    void set_side_to_move(Color c) { side = c; }

    const Hand& hand(Color c) const;
    Hand& hand(Color c);

    void make_move(const Move& m);
    void undo_move(const Move& m, Piece captured, Hand prevBlack, Hand prevWhite, Color prevSide);

    std::vector<Move> generate_legal_moves() const;

private:
    std::array<Piece, 81> board;
    Hand blackHand;
    Hand whiteHand;
    Color side;
};
