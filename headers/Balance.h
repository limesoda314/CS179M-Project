#ifndef BALANCE__H
#define BALANCE__H

#include <iostream>
#include <vector>
#include <fstream>
#include <string> 
#include<algorithm>
#include "Ship.h"
using namespace std; 

class BalanceShip {
    private:
        std::vector<std::pair<int,int>> coords;
        std::vector<std::string> mass; 
        std::vector<BalanceShip> children;
        std::vector<std::pair<int,int>> free_spaces;
        std::vector<std::pair<int,int>> move_spaces;   
         
    public: 
        // constructors 
        BalanceShip(const std::vector<pair<int,int>> &ship_coords, const std::vector<std::string> &ship_mass, const std::vector<std::string>&ship_names);  
        BalanceShip(const std::vector<pair<int,int>> &ship_coords, const std::vector<std::string> &ship_mass, const std::vector<pair<int,int>>& ship_free_spaces,const std::vector<pair<int,int>>& ship_move_spaces); 
        int expandNode(); 
        int generate_possible(); 
        int generate_move(); 
        int swap_coords(std::vector<pair<int,int>> &new_coords, const std::pair<int,int> &free_space, const std::pair<int,int> &move_space); 
        bool check_above(const int &y_coord, const int &x_coord);
        bool check_under(const int &y_coord, const int &x_coord); 
        bool check_under_mass(const int &y_coord, const int &x_coord);
}; 

#endif 