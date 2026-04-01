#pragma once
#include "position.h"
#include "eval.h"
#include "move.h"

Move search_best_move(Position& pos, const EvalWeights& w, int depth);
