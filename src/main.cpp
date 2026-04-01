#include "position.h"
#include "search.h"
#include "eval.h"
#include "learning.h"
#include "io.h"
#include <iostream>

GameResult self_play(EvalWeights& w) {
    Position pos;
    int moveCount = 0;

    while (true) {
        auto moves = pos.generate_legal_moves();
        if (moves.empty()) {
            GameResult r;
            r.winner = (pos.side_to_move() == Color::Black) ? -1 : 1;
            return r;
        }
        Move m = search_best_move(pos, w, 2);
        pos.make_move(m);
        moveCount++;
        if (moveCount > 200) {
            GameResult r;
            r.winner = 0;
            return r;
        }
    }
}

int main() {
    EvalWeights weights;
    load_weights(weights, "weights.dat");

    std::cout << "Current pawn value: " << weights.pawnValue << "\n";

    while (true) {
        std::cout << "Mode? (1: Human vs CPU, 2: Self-play train, 0: Exit): ";
        int mode;
        if (!(std::cin >> mode)) return 0;
        if (mode == 0) break;

        if (mode == 2) {
            std::cout << "Self-play games count: ";
            int n;
            std::cin >> n;
            for (int i = 0; i < n; ++i) {
                GameResult r = self_play(weights);
                update_weights_from_game(weights, r);
            }
            save_weights(weights, "weights.dat");
            std::cout << "Training done. New pawn value: " << weights.pawnValue << "\n";
            continue;
        }

        Position pos;
        while (true) {
            print_position(pos);
            auto moves = pos.generate_legal_moves();
            if (moves.empty()) {
                std::cout << "No legal moves. ";
                if (pos.side_to_move() == Color::Black) std::cout << "White wins.\n";
                else std::cout << "Black wins.\n";
                break;
            }

            if (pos.side_to_move() == Color::Black) {
                std::cout << "Your move (fromFile fromRank toFile toRank, e.g. 4 6 4 5): ";
                int ff, fr, tf, tr;
                std::cin >> ff >> fr >> tf >> tr;
                bool found = false;
                for (const auto& m : moves) {
                    if (m.fromFile == ff && m.fromRank == fr &&
                        m.toFile == tf && m.toRank == tr) {
                        pos.make_move(m);
                        found = true;
                        break;
                    }
                }
                if (!found) {
                    std::cout << "Illegal move.\n";
                    continue;
                }
            } else {
                std::cout << "CPU thinking...\n";
                Move m = search_best_move(pos, weights, 2);
                std::cout << "CPU plays: " << move_to_string(m) << "\n";
                pos.make_move(m);
            }
        }

        GameResult r;
        // 超適当：最後に手番が動けない側が負け
        r.winner = (pos.side_to_move() == Color::Black) ? -1 : 1;
        update_weights_from_game(weights, r);
        save_weights(weights, "weights.dat");
        std::cout << "Updated pawn value: " << weights.pawnValue << "\n";
    }

    return 0;
}
