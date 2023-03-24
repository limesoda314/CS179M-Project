#ifndef SHIP__H
#define SHIP__H

#include <iostream>
#include <vector>
#include <fstream>
#include <string> 
#include<algorithm>
using namespace std; 

class Ship {
    private:
        vector<pair<int,int>> Coordinates; 
        vector<string> Mass; 
        vector<string> Names;
        string manifest_name = ""; 

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
        string get_manifest_name() const {return manifest_name; }

        // END GETTERS

        // START MAIN OPERATIONS

        /* Option 1 - Loads the manifest into our internal representation of container coordinates,
                      names, masses, and manifest_name */
        int load_manifest(const string &filepath);

        /* Option 2 - Outputs the manifest onto the console */
        int read_manifest(); // likely for development/testing only  

        /* Option 3 - Creates an outbound manifest based on the current representation of internal
        variables within Ship class */
        int create_outbound(); 

        /* Option 4 - Allows operator to input comment */
        int log_comment(const string &comment);

        /* Option 5 - Prints out the entire log file */
        int view_logfile(); 

        /* Option 6 - Prints the current state of the Ship class internal variables */
        int print_ship() const; 

        /* Option 7 - Prints out the balance score of the current ship */
        double balance_score() const; // TODO

        /* Option 8 - Performs balancing operations */
        int balance_ship(); // TODO

        /* Option 9 - Load/Unload contains from and to ship */
        int load_unload_ship();

        /* Option q - Already built into the main.cpp source file */
        // ---

        // END MAIN OPERATIONS
    
    // START HELPERS
    private:
        double print_balance_info(vector<pair<int, int>>&, vector<pair<int,int>>&, const double &, const double &);
        void calculate_possible_places(vector<int> &, int, int); 
        void calculate_best_manhattan(vector<pair<int,int>> &, vector<int> &, vector<double> &, vector<int> &);
        void calculate_best_place(int&, int &, const vector<int> &, const vector<double> &, const vector<pair<int,int>> &); 
        double calculate_manhattan(int index_a, int index_b) const;  
        void calculate_swap_coordinates(double &, double &, const int &, const vector<int>&, vector<pair<int, int>> &, vector<pair<int, int>> &);
        double calculate_manhattan(int y_1, int x_1, int y_2, int x_2) const;  

    // END HELPERS

}; 

#endif // SHIP.H