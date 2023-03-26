#ifndef SHIP__H
#define SHIP__H

#include <iostream>
#include <vector>
#include <fstream>
#include <string> 
#include <algorithm> 
#include <queue>
#include <ctime>

class Ship {
    private:
        std::vector<std::pair<int,int>> Coordinates; 
        std::vector<std::string> Mass; 
        std::vector<std::string> Names;
        std::string manifest_name = ""; 

        // needed for balance and onload/offload
        // std::priority_queue<BalanceShip*, std::vector<BalanceShip*>, > frontier;

    public: 
        // constructors 
        Ship() {}; 

        // START MANIFEST OPERATIONS

        /* Resets the ship variables entirely */
        int reset_ship(); // so we can load again

        // END MANIFEST OPERATIONS
        
        // START LOGFILE OPERATIONS

        // END LOGFILE OPERATIONS

        // START GETTERS

        /* Gets the manifest name */
        std::string get_manifest_name() const {return manifest_name; }

        // END GETTERS

        // START MAIN OPERATIONS

        /* Option 1 - Loads the manifest into our internal representation of container coordinates,
                      names, masses, and manifest_name */
        int load_manifest(const std::string &filepath);

        /* Option 2 - Outputs the manifest onto the console */
        int read_manifest(); // likely for development/testing only  

        /* Option 3 - Creates an outbound manifest based on the current representation of internal
        variables within Ship class */
        int create_outbound(); 

        /* Option 4 - Allows operator to input comment */
        int log_comment(const std::string &comment);

        /* Option 5 - Prints out the entire log file */
        int view_logfile(); 

        /* Option 6 - Prints the current state of the Ship class internal variables */
        std::string print_ship() const;

        /* Option 7 - Prints out the balance score of the current ship */
        double balance_score() const; // TODO

        /* Option 8 - Performs balancing operations */
        // int balance_ship();

        /* Option 9 - Load/Unload contains from and to ship */
        int load_unload_ship();

        /* Option 10 - Balgitance */
        std::vector<std::pair<int,int>> balance_list();

        std::string swap_coordinates(std::pair<int,int>& coord1, std::pair<int,int>& coord2);

        void save_ship_states(std::vector<std::string> &, std::vector<std::pair<int, int>> );

        std::vector<std::pair<int,int>> getCoords() const { return this->Coordinates; }
        std::vector<std::string> getMasses() const { return this->Mass; }
        std::vector<std::string> getNames() const { return this->Names; }

        /* Option q - Already built into the main.cpp source file */
        // ---

        // END MAIN OPERATIONS
    
    // START HELPERS
    private:
        double print_balance_info(std::vector<std::pair<int, int>>&, std::vector<std::pair<int,int>>&, const double &, const double &);
        void calculate_possible_places(std::vector<int> &, int, int); 
        void calculate_best_manhattan(std::vector<std::pair<int,int>> &, std::vector<int> &, std::vector<double> &, std::vector<int> &);
        void calculate_best_place(int&, int &, const std::vector<int> &, const std::vector<double> &, const std::vector<std::pair<int,int>> &); 
        double calculate_manhattan(int index_a, int index_b) const;  
        void calculate_swap_coordinates(double &, double &, const int &, const std::vector<int>&, std::vector<std::pair<int, int>> &, std::vector<std::pair<int, int>> &);
        double calculate_manhattan(int y_1, int x_1, int y_2, int x_2) const;  

    // END HELPERS
}; 

#endif // SHIP.H
