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

        // manifest 
        int load_manifest(const string &filepath); 
        int read_manifest();                            // likely for development/testing only 
        int create_outbound();  
        int reset_ship(); // so we can load again
        int print_ship() const; 
        

        // logfile 
        int log_comment(const string &comment);
        int view_logfile(); 
        string get_manifest_name() const {return manifest_name; }


        // TODO: operations 
        double balance_score() const; 
        int balance_ship();
        double calculate_manhattan(int index_a, int index_b) const;  
        // pass in the index to a coordinate 
        double calculate_manhattan(int y_1, int x_1, int y_2, int x_2) const;  

}; 

#endif 