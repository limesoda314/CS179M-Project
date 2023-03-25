#ifndef __SHIPPINGPORTDRIVER_H__
#define __SHIPPINGPORTDRIVER_H__

// Currently just using C++ STD Queue
#include <queue>
#include <set>
#include "ShipState.h"
#include <string>
#include <iostream>

/* Comparator to push ShipState poiters into priority queue */
class Comp {
    public:
        bool operator()(ShipState* a, ShipState* b) {
            return ((a->f_valueFrom() ) > ( b->f_valueFrom()));
        }
};

/* Pretty much the AStar class */
class ShippingPortDriver {

    private:
        std::priority_queue<ShipState*, std::vector<ShipState*>, Comp> frontier;
        std::set<ShipState*> frontier_set;
        std::set<ShipState*> explored;
        int count;
        int maxFrontierLength;
        Ship* root;

    public:
        // Constructors
        ShippingPortDriver();

        // Control
        ShipState* graphSearch(ShipState*);
        void menu();
        void printPath(std::ostream&, ShipState*, int);
        void defaultTest();
};

#endif