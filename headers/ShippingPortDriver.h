#ifndef __SHIPPINGPORTDRIVER_H__
#define __SHIPPINGPORTDRIVER_H__

// Currently just using C++ STD Queue
#include <queue>
#include <set>
#include "ShipState.h"
#include <string>
#include <iostream>
#include <ctime>

#include "./Ship.h"

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
        Ship* ship;
        std::vector<std::pair<int, int>> balance_list;
        std::vector<std::pair<int, int>> transfer_list;
        ShipState* startState;

    public:
        // Constructors
        ShippingPortDriver();

        // Control
        ShipState* graphSearch(ShipState*);
        
        void menu();
        
        void printPath(std::ostream&, ShipState*, int i);
        
        void defaultTest();

        void balance_ship(std::vector<std::pair<int, int>>&);
        void balance_ship_impossible();

        void drawBalanceList(std::ostream&) const;

        Ship* getShip() const { return this->ship; }


        void setShip(Ship*);

        int QTGUI(int, char**);

        void cleanInternalVariables(std::ostream&);

        void clearShipStateTree(ShipState*, std::ostream&);

        void transfer_containers(std::vector<std::pair<int, int>>&);
};

#endif
