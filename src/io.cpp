#include "io.h"
#include <iostream>

void print_position(const Position& pos) {
    for (int r = 0; r < 9; ++r) {
        for (int f = 0; f < 9; ++f) {
            Piece p = pos.piece_at(f, r);
            char c = '.';
            switch (p) {
            case Piece::BPawn: c = 'P'; break;
            case Piece::BKing: c = 'K'; break;
            case Piece::WPawn: c = 'p'; break;
            case Piece::WKing: c = 'k'; break;
            default: c = '.';
            }
            std::cout << c << ' ';
        }
        std::cout << "\n";
    }
    std::cout << (pos.side_to_move() == Color::Black ? "Side: Black\n" : "Side: White\n");
}

std::string move_to_string(const Move& m) {
    std::string s;
    s += char('1' + m.fromFile);
    s += char('a' + m.fromRank);
    s += '-';
    s += char('1' + m.toFile);
    s += char('a' + m.toRank);
    return s;
}
