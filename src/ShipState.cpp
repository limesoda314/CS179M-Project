#include "../headers/ShipState.h"
#include <iostream>

ShipState::ShipState(
    const std::vector<std::pair<int,int>>& ship_coords,
    const std::vector<std::string>& ship_mass,
    const std::vector<std::string>& ship_names,s
    Heuristic* ctx,
    ShipState* par
    )
{
    std::cout << "      into ShipState constructor" << std::endl;

    this->ctx = ctx;

    this->cost = 0; 

    // push back only coordinates that have a cargo or are part of the ship 
    for (int i = 0; i < ship_names.size(); i++) {
        std::cout << "      curr name..." << ship_names.at(i) << std::endl;
        std::cout << "      curr coords... ("
                  << ship_coords.at(i).first
                  << ", "
                  << ship_coords.at(i).second << ")" << std::endl;
        if (ship_names.at(i) == "NAN") {
            this->mass.push_back("NAN");
            this->coords.push_back(ship_coords.at(i)); 
        } 
        else if (ship_names.at(i) != "UNUSED") {
            this->mass.push_back(ship_mass.at(i)); 
            this->coords.push_back(ship_coords.at(i)); 
        }
    } 

    std::cout << "      > Finished copying the coordinates" << std::endl;

    std::cout << "      > Generate possible free spaces" << std::endl;
    this->generate_possible(); 

    std::cout << "      > Generate possible moves to make" << std::endl;
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
            std::vector<std::pair<int,int>> new_frees =  this->free_spaces; // free_spaces.at(j) is now move_spaces.at(i)
            std::vector<std::pair<int,int>> new_moves =  this->move_spaces; // update move_spaces.at(i) to be coordinate underneath if y_coord > 1 pair<int,int> (move_spaces.at(i).first, move_spaces.at(i).second - 1) 
            
            // check if free space is ontop of a box 
            // if it is, we need to remove it from the possible spaces later 
            // if (this->check_under_mass(free_spaces.at(j).first, free_spaces.at(j).second)) {
            //     for (int k = 0; k < new_moves.size(); k++) {
            //         if (new_moves.at(k).first == free_spaces.at(j).first-1 && new_moves.at(k).second == free_spaces.at(j).second) {
            //             new_moves.at(k) = new_moves.at(new_moves.size() - 1);
            //             new_moves.pop_back();  
            //         }
            //     }
            // }

            // // update temp coord and mass vectors
            // swap_coords(new_coords, move_spaces.at(i), free_spaces.at(j)); 
            // new_frees.at(j) = move_spaces.at(i);

            // if (move_spaces.at(i).first > 1) {
            //     new_moves.at(i) = std::pair<int,int> (move_spaces.at(i).first-1, move_spaces.at(i).second);
            // }
            
            // ShipState* newState = new ShipState(
            //     new_coords,
            //     this->mass,
            //     new_frees,
            //     new_moves, 
            //     this->ctx,
            //     this
            // );

            // newState->setCost(this->getCost() + 1);
            // children.push_back(newState); 

            // Remove current item from free_spaces and move_spaces
            // for (int k = 0; k < this->free_spaces.size(); k++) {
            //     if 
            // }

        
            // First update value in new_coords to reflect change (it will reflect free_spaces[j] coords)
            for (int k = 0; k < new_coords.size(); k++) {
                if ( new_coords.at(k).first == new_moves.at(i).first && new_coords.at(k).second == new_moves.at(i).second ) {
                    new_coords.at(k).first = new_moves.at(i).first;
                    new_coords.at(k).second = new_moves.at(i).second;
                }
            }

            // Update new moves to reflect the change (new move will add both the current free_space and the one below
            // the old new_moves)
            new_moves.at(i)

            // Update free spaces to now reflect the change (free_spaces[j].first - 1 for y)
            free_spaces.at(j).first = free_spaces.at(j).first - 1;
        
            // Update new moves to reflect the change (new move will add both the current free_space)

            // 
            for () {

            }
        
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
        if (new_coords.at(i).first == move_space.first && new_coords.at(i).second == move_space.second) {
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

        std::pair<int, int> curr_iter = this->coords.at(i);

        if (
            !coordInCoords(std::pair<int, int>(curr_iter.first+1, curr_iter.second))
        ) {

            // 8+1 comes from the top in terms of indexing [1, size] (0+1, size-1+1)
            if (curr_iter.first+1 >= 8+1) {
                continue;
            }    

            // we can not move NAN boxes 
            if (mass.at(i) != "NAN") {
                move_spaces.push_back(coords.at(i)); 
            }

        }
    }
    if (move_spaces.size() <= 12) {
        return 1; 
    }

    return -1;
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
int ShipState::generate_possible() {

    int max_top = 8 + 1; // maximum y index [1, y_size]
    int max_right = 12 + 1; // maximum x index [1, x_size]

    std::pair<int, int> curr_coord(0, 0);

    // Get free spaces from the current boxes row
    for (int i = 0; i < 12; i++) { // thru x
        for (int j = 0; j < 8; j++) { // thru y
            curr_coord.first = j+1;
            curr_coord.second = i+1;

            // iterate through every coord, check if we have a possible free space
            for (int k = 0; k < this->coords.size(); k++) {
                // i corresponds to second (x axis)
                // j corresponds to first  (y axis)
                if (this->coords.at(k).second == i+1) {
                    // check for add to free spaces
                    if (
                            ((j+1-1) == this->coords.at(k).first) &&
                            !coordInCoords(curr_coord)
                    ) {
                        this->free_spaces.push_back(std::pair<int, int>(j+1, i+1));   
                    }
                }
            }
        }
    }

    // Get any other free spaces :> (empty slots, so only first row)
    for (int i = 0; i < 12; i++) {
        curr_coord.first = 0+1;
        curr_coord.second = i+1;
        if (!coordInCoords(curr_coord)) {
            this->free_spaces.push_back(std::pair<int, int>(0+1, i+1));
        }
    }

    // number of possible spaces is 12
    if (free_spaces.size() <= 12) {
        return 1; 
    }

    return -1;        
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
        out << "(" << this->coords.at(i).first << "," << this->coords.at(i).second << ")["
        << this->mass.at(i) << "], ";
    }
    out << "}" << std::endl;
    return;
}

int ShipState::balanceFactor() const {
    int right_mass = 0;
    int left_mass = 0;
    int middle = (11 - 0 + 1) / 2; // 6 - middle of the ship

    for (int i = 0; i < this->coords.size(); i++) {
        // std::cout << "                      mass: " << this->mass.at(i) << std::endl;
        if (this->mass.at(i) != "NAN") {
            if (this->coords.at(i).second <= middle) {
                left_mass += std::stoi(this->mass.at(i));
            }
            else {
                right_mass += std::stoi(this->mass.at(i)); 
            }
        }
    }

    double balance = 0.0; 
 
    // std::cout << "               left_mass: " << left_mass << std::endl;
    // std::cout << "               right_mass: " << right_mass << std::endl;

    if (left_mass > right_mass) {
        balance = (right_mass * 1.0) / left_mass; 
    }
    else {
        balance = (left_mass * 1.0) / right_mass; 
    }

    // std::cout << "Ship has a balance score of: " << balance << std::endl;
    // std::cout << "right: " << right_mass << std::endl;
    // std::cout << "left: " <<left_mass << std::endl;
    std::cout << "               BALANCE: " << balance << std::endl;
    return balance;
}

bool ShipState::coordInCoords(std::pair<int, int> curr){
    for (int i = 0; i < this->coords.size(); i++) {
        if ((this->coords.at(i).first == curr.first) &&
            (this->coords.at(i).second == curr.second)) {
                return true;
        }
    }
    return false;
}

void ShipState::drawCoords(
    std::ostream& out,
    std::vector<std::pair<int, int>>
) const {


    return;
}