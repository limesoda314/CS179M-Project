#include "../headers/HeuristicStrategy.h"
#include "../headers/ShipState.h"
#include <math.h>

Heuristic::Heuristic() {}

BalanceFactorHeuristic::BalanceFactorHeuristic() : Heuristic() {}
double BalanceFactorHeuristic::heuristic(const ShipState* shipState) const {
    return std::fabs(1 - shipState->balanceFactor());
}

UniformCostHeuristic::UniformCostHeuristic() : Heuristic() {}
double UniformCostHeuristic::heuristic(const ShipState* shipState) const { return 0; }
