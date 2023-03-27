#ifndef SHIP__H
#define SHIP__H

#include <iostream>
#include <vector>
#include <fstream>
#include <string> 
#include <algorithm> 
#include <cmath>
#include <queue>
#include <ctime>

class Ship {
    private:
        std::vector<std::pair<int,int>> Coordinates; 
        std::vector<std::string> Mass; 
        std::vector<std::string> Names;
        std::string manifest_name = "";

    public: 
        std::vector<std::string> saved_states; // printed ship states
        std::vector<std::pair<int,int>> balanced_list;
        std::vector<std::pair<int,int>> transfer_moves;
        std::pair <int,int> move_num; // move_num, list size
        std::vector<std::string> load_mass;
        std::vector<std::string> load_names;
        std::vector<std::string> unload_quantity;
        std::vector<std::string> unload_names;
        // constructors 
        Ship() {}; 

        // START MANIFEST OPERATIONS

        /* Resets the ship variables entirely */
        int reset_ship(); // so we can load again

        int isPossibleToBalance() const; // 0 for impossible, 1 for possible, 2 for idk we have to check the sum of permuations

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
        int create_outbound(std::string file_path);

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

        /* Option 10 - Balance */
        std::vector<std::pair<int,int>> create_balance_list();
        int balance_list(std::vector<std::pair<int,int>> &);
        std::vector<std::pair<int, int>> balance_list();
        /* Option 11 - Unload/load */
        std::vector<std::pair<int,int>> create_transfer_moves();
        int create_transfer_list(std::vector<std::pair<int,int>> &);

        // swap two coordinates and return the ship state (string, print_ship funct call)
        std::string swap_coordinates(std::pair<int,int>& coord1, std::pair<int,int>& coord2);

        // saves the ship state (printed) as a string
        // can use to print
        void save_ship_states(std::vector<std::string> &, std::vector<std::pair<int, int>> ); // same function, however one uses a saved_state vector in Ship class
        void save_ship_states(std::vector<std::pair<int, int>> );
        int num_boxes() const;

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
