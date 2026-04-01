#include "learning.h"
#include <fstream>

void load_weights(EvalWeights& w, const std::string& path) {
    std::ifstream ifs(path);
    if (!ifs) return;
    ifs >> w.pawnValue >> w.kingSafety;
}

void save_weights(const EvalWeights& w, const std::string& path) {
    std::ofstream ofs(path);
    if (!ofs) return;
    ofs << w.pawnValue << " " << w.kingSafety << "\n";
}

void update_weights_from_game(EvalWeights& w, const GameResult& result) {
    // 超適当な学習ルール：
    // 先手が勝ったら歩の価値を+1、後手が勝ったら-1
    if (result.winner == 1) {
        w.pawnValue += 1;
    } else if (result.winner == -1) {
        w.pawnValue -= 1;
    }

    if (w.pawnValue < 10) w.pawnValue = 10;
    if (w.pawnValue > 1000) w.pawnValue = 1000;
}
