#ifndef SHIPSTATE__H
#define SHIPSTATE__H

#include <vector>
#include <fstream>
#include <string> 
#include <algorithm>

#include "../headers/HeuristicStrategy.h"

/* Stores the current state of the containers within a ship */
class ShipState {
    private:
        // physical coordinates
        std::vector<std::pair<int,int>> coords;

        // masses 
        std::vector<std::string> mass;

        // contains every possible (perhaps not every possible one, given
        // a heuristic-based graph search algorithm) ShipState given the
        // free_spaces and move_spaces vectors
        std::vector<ShipState*> children;

        // possible places to move boxes into - literally the spaces above 
        // the surface of the container boxes
        std::vector<std::pair<int,int>> free_spaces;

        // every box that can move - the surface of the container boxes
        std::vector<std::pair<int,int>> move_spaces;

        // load and unload names and masses
        std::vector<std::string> unload_names;
        std::vector<std::string> unload_mass;
        std::vector<std::string> load_names;
        std::vector<std::string> load_mass;

        Heuristic* ctx;
        ShipState* parent;

        std::pair<int, int> currFrom;
        std::pair<int, int> currTo;

        int cost;

    public: 
        // constructors 
        ShipState(
            const std::vector<std::pair<int,int>> &ship_coords,
            const std::vector<std::string> &ship_mass,
            const std::vector<std::string>& ship_names,
            Heuristic* ctx,
            ShipState* par
        );  

        ShipState(
            const std::vector<std::pair<int,int>> &ship_coords,
            const std::vector<std::string> &ship_mass,
            const std::vector<std::pair<int,int>>& ship_free_spaces,
            const std::vector<std::pair<int,int>>& ship_move_spaces,
            Heuristic* ctx,
            ShipState* par
        ); 

        /* Expands node into its possibility of movements */
        int expandNode(); 

        /* Generates possible spaces to move boxes to */
        int generate_possible(); 

        /* Generates possible boxes we can make */
        int generate_move(); 
        
        /* Updates new coordinates given the free coordinates and move coordinates */
        int swap_coords(
            std::vector<std::pair<int,int>> &new_coords,
            const std::pair<int,int> &free_space,
            const std::pair<int,int> &move_space);

        /* Check above a certain x,y position */
        bool check_above(const int &y_coord, const int &x_coord);

        /* Check under a certain x,y position */
        bool check_under(const int &y_coord, const int &x_coord);

        /* Check under a certain x,y mass position */ 
        bool check_under_mass(const int &y_coord, const int &x_coord);

        /* Calculate f factor for current ship state */
        double f_valueFrom() const;

        /* Calculates the heuristic of the board state for the current
        selected context */
        double heuristic() const;

        int getCost() const { return this->cost; }
        void setCost(int cst) { this->cost = cst; }

        void setContext(Heuristic* ctx);

        // Overloading == operator for the GameDrive driver
        friend bool operator==(ShipState& lhs, ShipState& rhs);

        ShipState* getChild(int i) const;
        ShipState* getParent() const { return this->parent; }

        int getChildrenLength() const { return this->children.size(); }

        std::vector<std::pair<int,int>> getCoords() const { return this->coords; }
        std::vector<std::string> getMass() const { return this->mass; }

        void draw(std::ostream&);
        void drawChange(std::ostream&, std::vector<std::pair<int, int>>&);
        void drawFree(std::ostream&);
        void drawMoves(std::ostream&);

        double balanceFactor() const;

        bool coordInCoords(std::pair<int, int>);

        std::pair<int, int> getCurrFrom() const { return this->currFrom; }
        std::pair<int, int> getCurrTo() const { return this->currTo; }

        bool finished() const;

    private:
        void drawCoords(std::ostream&, std::vector<std::pair<int, int>>) const;
};

#endif 
