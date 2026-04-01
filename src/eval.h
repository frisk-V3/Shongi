#pragma once
#include "position.h"

struct EvalWeights {
    int pawnValue = 100;
    int kingSafety = 0; // ここではダミー
};

int evaluate(const Position& pos, const EvalWeights& w);
