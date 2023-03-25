#include "../headers/ShipState.h"
#include <iostream>

ShipState::ShipState(
    const std::vector<std::pair<int,int>>& ship_coords,
    const std::vector<std::string>& ship_mass,
    const std::vector<std::string>& ship_names,
    Heuristic* ctx,
    ShipState* par
    )
{
    // push back only coordinates that have a cargo or are part of the ship 
    for (int i = 0; i < ship_names.size(); i++) {
        if (ship_names.at(i) == "NAN") {
            this->mass.push_back("NAN"); 
            this->coords.push_back(ship_coords.at(i)); 
        } 
        else if (ship_names.at(i) != "UNUSED" && ship_names.at(i) != "NAN") {
            this->mass.push_back(ship_names.at(i)); 
            this->coords.push_back(ship_coords.at(i)); 
        }
    } 

    this->generate_possible(); 
    this->generate_move(); 
}

ShipState::ShipState(
    const std::vector<std::pair<int,int>> &ship_coords,
    const std::vector<std::string> &ship_mass,
    const std::vector<std::pair<int,int>>& ship_free_spaces,
    const std::vector<std::pair<int,int>>& ship_move_spaces,
    Heuristic* ctx,
    ShipState* par
    )
{
    this->coords = ship_coords;
    this->mass = ship_mass; 
    this->free_spaces = ship_free_spaces; 
    this->move_spaces = ship_move_spaces;
    this->cost = 0;
    this->ctx = ctx;
    this->parent = par;
} 

int ShipState::expandNode() {

    for (int i = 0; i < move_spaces.size(); i++) {
        
        for (int j = 0; j < free_spaces.size(); j++) {
            std::vector<std::pair<int,int>> new_coords = this->coords; 
            //vector<std::string> new_mass =          this->mass;
            std::vector<std::pair<int,int>> new_frees =  this->free_spaces; // free_spaces.at(j) is now move_spaces.at(i)
            std::vector<std::pair<int,int>> new_moves =  this->move_spaces; // update move_spaces.at(i) to be coordinate underneath if y_coord > 1 pair<int,int> (move_spaces.at(i).first, move_spaces.at(i).second -1) 
            
            // check if free space is ontop of a box 
            // if it is, we need to remove it from the possible spaces later 
            if (check_under_mass(free_spaces.at(j).first, free_spaces.at(j).second)) {
                for (int k = 0; k < new_moves.size(); k++) {
                    if (new_moves.at(k).first == free_spaces.at(j).first-1 && new_moves.at(k).second == free_spaces.at(j).second) {
                        new_moves.at(k) = new_moves.at(new_moves.size()-1);
                        new_moves.pop_back();  
                    }
                }
            }

            // update temp coord and mass vectors
            swap_coords(new_coords, move_spaces.at(i), free_spaces.at(j)); 
            new_frees.at(j) = move_spaces.at(i); 

            if (move_spaces.at(i).first > 1) {
                new_moves.at(i) = std::pair<int,int> (move_spaces.at(i).first-1, move_spaces.at(i).second);
            }
            
            children.push_back(
                new ShipState(
                    new_coords,
                    this->mass,
                    new_frees,
                    new_moves, 
                    this->ctx,
                    this
                )
            ); 

        }

    }

    return 0;

}

int ShipState::swap_coords(
    std::vector<std::pair<int,int>> &new_coords,
    const std::pair<int,int> &free_space,
    const std::pair<int,int> &move_space)

{
    
    // free_space should not exist in new_coords 
    int move_index = 0;   
    for (int i = 0; i < new_coords.size(); i++) {
        if (new_coords.at(i) == move_space) {
            move_index = i; 
            break;
        }
    }
    
    // update new_coords
    new_coords.at(move_index) = free_space; // updating coordinate, index of enw coordinates still same in relation to mass 
    // don't need to update new_mass since we're only moving the cargo 
    
    return 1; 
}

int ShipState::generate_move() {
    for (int i = 0; i < this->coords.size(); i++) {
        if (!check_above(coords.at(i).first, coords.at(i).second)) {
            // we can not move NAN boxes 
            if (mass.at(i) != "NAN") {
                move_spaces.push_back(coords.at(i)); 
            }
        }
    }
    if (move_spaces.size() <= 12) {
        return 1; 
    }
}

bool ShipState::check_above(const int &y_coord, const int &x_coord) {
    for (int i = 0; i < this->coords.size(); i++) {
        if (this->coords.at(i).first == y_coord +1 && this->coords.at(i).second == x_coord) {
            return 1; 
        }
    }
    return 0; 
}

// can possibly update implementation later to check going up 
// this way you can avoid checking columns that are empty 
// TODO: check upper height 
int ShipState::generate_possible() {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 12; j++) {
        
            if (i == 0) { // first level spaces are all fine as long as there isn't something there 
                if (coords.at(i).first != i+1 && coords.at(i).second != j+1) {
                    this->free_spaces.push_back(std::pair<int,int>(i+1, j+1)); 
                } 
            }
            else {  // need to check if there is a box underneath for every level other than first  
                if (coords.at(i).first != i+1 && coords.at(i).second != j+1) {
                    if (check_under(i+1, j+1)) {
                        this->free_spaces.push_back(std::pair<int,int>(i+1, j+1)); 
                    }
                }

            }
        }
    }
    // number of possible spaces is 12
    if (free_spaces.size() <= 12) {
        return 1; 
    }
         
}

bool ShipState::check_under(const int &y_coord, const int &x_coord) {
    if (y_coord == 1) {
        return 0; 
    }
    for (int i = 9; i < this->coords.size(); i++) {
        if (coords.at(i).first == y_coord-1 && coords.at(i).second == x_coord) {
            return 1; // true
        }
    }
    return 0; // false 
}

bool ShipState::check_under_mass(const int &y_coord, const int &x_coord) {
    if (y_coord == 1) {
        return 0; 
    }
    for (int i = 9; i < this->coords.size(); i++) {
        if (coords.at(i).first == y_coord-1 && coords.at(i).second == x_coord) {
            if (mass.at(i) == "NAN") {
                return false; 
            }
            return 1; // true
        }
    }
    return 0; // false 
}

int ShipState::f_valueFrom() const {
    return this->getCost() + this->heuristic();
}

int ShipState::heuristic() const {
    return this->ctx->heuristic(this);
}

// overloads
bool operator==(ShipState& lhs, ShipState& rhs) {
    std::vector<std::pair<int, int>> lhsCoords = lhs.coords;
    std::vector<std::pair<int, int>> rhsCoords = rhs.coords;

    for (int i = 0; i < lhsCoords.size(); i++) {
        if (lhsCoords.at(i) != rhsCoords.at(i)) {
            return false;
        }
    }

    return true;
}

void ShipState::draw(std::ostream& out) {
    out << "Drawing board with coords {";
    for (int i = 0; i < this->coords.size(); i++) {
        out << "(" << this->coords.at(i).first << "," << this->coords.at(i).second << "), ";
    }
    out << "}" << std::endl;
    return;
}