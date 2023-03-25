#ifndef __HEURISTIC_STRATEGY_H__
#define __HEURISTIC_STRATEGY_H__

#include <cmath>

class ShipState;

class Heuristic {

    public:
        Heuristic();
        virtual int heuristic(const ShipState*) const = 0;
};

// Balance heuristics
class BalanceFactorHeuristic : public Heuristic {

    public:
        BalanceFactorHeuristic();
        virtual int heuristic(const ShipState*) const override;
};

// Uniform cost heuristic
class UniformCostHeuristic : public Heuristic {

    public:
        UniformCostHeuristic();
        virtual int heuristic(const ShipState*) const override;
};

#endif // HEURISTICSTRATEGY.H