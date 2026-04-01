#pragma once
#include "eval.h"
#include <string>

struct GameResult {
    int winner; // 1: Black, -1: White, 0: draw
};

void load_weights(EvalWeights& w, const std::string& path);
void save_weights(const EvalWeights& w, const std::string& path);

// 超シンプルな「自己対局結果から重みを微調整」する関数
void update_weights_from_game(EvalWeights& w, const GameResult& result);
