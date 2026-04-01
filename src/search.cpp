#include "search.h"
#include <limits>

static int alphabeta(Position& pos, const EvalWeights& w, int depth, int alpha, int beta) {
    if (depth == 0) {
        return evaluate(pos, w);
    }

    auto moves = pos.generate_legal_moves();
    if (moves.empty()) {
        // 負け扱い
        return -1000000;
    }

    int best = std::numeric_limits<int>::min();
    for (const auto& m : moves) {
        Hand prevB = pos.hand(Color::Black);
        Hand prevW = pos.hand(Color::White);
        Color prevSide = pos.side_to_move();
        Piece captured = pos.piece_at(m.toFile, m.toRank);

        pos.make_move(m);
        int score = -alphabeta(pos, w, depth - 1, -beta, -alpha);
        pos.undo_move(m, captured, prevB, prevW, prevSide);

        if (score > best) best = score;
        if (score > alpha) alpha = score;
        if (alpha >= beta) break;
    }
    return best;
}

Move search_best_move(Position& pos, const EvalWeights& w, int depth) {
    auto moves = pos.generate_legal_moves();
    Move bestMove;
    int bestScore = std::numeric_limits<int>::min();

    for (const auto& m : moves) {
        Hand prevB = pos.hand(Color::Black);
        Hand prevW = pos.hand(Color::White);
        Color prevSide = pos.side_to_move();
        Piece captured = pos.piece_at(m.toFile, m.toRank);

        pos.make_move(m);
        int score = -alphabeta(pos, w, depth - 1, std::numeric_limits<int>::min() + 1,
                               std::numeric_limits<int>::max());
        pos.undo_move(m, captured, prevB, prevW, prevSide);

        if (score > bestScore) {
            bestScore = score;
            bestMove = m;
        }
    }

    return bestMove;
}
