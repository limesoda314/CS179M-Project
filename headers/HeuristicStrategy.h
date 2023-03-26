#ifndef __HEURISTIC_STRATEGY_H__
#define __HEURISTIC_STRATEGY_H__

#include <cmath>

class ShipState;

class Heuristic {

    public:
        Heuristic();
        virtual double heuristic(const ShipState*) const = 0;
};

// Balance heuristics
class BalanceFactorHeuristic : public Heuristic {

    public:
        BalanceFactorHeuristic();
        virtual double heuristic(const ShipState*) const override;
};

// Uniform cost heuristic
class UniformCostHeuristic : public Heuristic {

    public:
        UniformCostHeuristic();
        virtual double heuristic(const ShipState*) const override;
};

#endif // HEURISTICSTRATEGY.H