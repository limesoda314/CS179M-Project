#ifndef BALANCE__H
#define BALANCE__H

#include <iostream>
#include <vector>
#include <fstream>
#include <string> 
#include<algorithm>
#include "Ship.h"
using namespace std; 

class ShipState {
    private:
        Ship *BalanceShip;
         
    public: 
        // constructors 
        ShipState   (Ship *ship) : BalanceShip(ship) {}

        double balance_score() const; 
        int balance_ship();
        double calculate_manhattan(int index_a, int index_b) const;  
        // pass in the index to a coordinate 
        double calculate_manhattan(int y_1, int x_1, int y_2, int x_2) const;  

}; 

#endif 