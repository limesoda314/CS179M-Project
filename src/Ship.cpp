#include "../headers/Ship.h"

int Ship::reset_ship() {
    manifest_name = ""; 
    Coordinates.clear();
    Mass.clear();
    Names.clear();

    if (Names.size() != 0 || Coordinates.size() != 0 || Names.size() != 0) {
        return -1; 
    }

    return 0; 
}

// load manifest from filepath
int Ship::load_manifest(const std::string &filepath) {
    if (manifest_name != "") {
        reset_ship(); 
    }
    
    std::fstream fin(filepath); 
    
    // save manifest name 
    for (int i = filepath.size()-1; i >=0; i--) {
        if (filepath.at(i) == '/' || filepath.at(i) == '\\') {
            break; 
        } 
        this->manifest_name = filepath.at(i) + this->manifest_name; 
    }
    this->manifest_name = this->manifest_name.substr(0, manifest_name.size()-4); 

    if (!fin.is_open()) {
        std::cout << "Error opening file, please try again" << std::endl;
        return -1; 
    }
 
    while(!fin.eof()) {
        std::string cargo_y;
        std::string cargo_x;
        std::string cargo_mass;
        std::string cargo_name;

        getline(fin, cargo_y, ','); 
        getline(fin, cargo_x, ',');
        std::cout << stoi(cargo_x.substr(0, 2)) << std::endl; 
        std::cout << stoi(cargo_y.substr(1, 2)) << std::endl; 
        this->Coordinates.push_back(std::pair<int,int> ( stoi(cargo_y.substr(1,2)),  stoi(cargo_x.substr(0,2)) )); 
        getline(fin, cargo_mass, ','); 
        std::cout << cargo_mass.substr(2, cargo_mass.length() - 3) << std::endl;
        this->Mass.push_back(cargo_mass.substr(2, cargo_mass.length()-3)); 
        
        getline(fin, cargo_name);

        // cargo_name = cargo_name.substr(1, cargo_name.length() - 1);

        std::cout << cargo_name.substr(1, cargo_name.length() - 1) << std::endl;

        this->Names.push_back(cargo_name.substr(1, cargo_name.length() - 1));
       
    }
    
    fin.close(); 

//    std::string comment = "Uploaded Manifest " + manifest_name + ".txt";
    // log_comment(comment);


    return 0;
}

// output manifest contents to console 
int Ship::read_manifest() {
    std::cout << "Manifest" << std::endl; 
    for (unsigned int i = 0 ; i < Coordinates.size(); i++) {
        std::cout << "coordinates: ";
        if (Coordinates.at(i).first < 10) {
            std::cout << " "; 
        }
        std::cout << Coordinates.at(i).first << ", ";
        if (Coordinates.at(i).second < 10) {
            std::cout << " "; 
        }
        std::cout << Coordinates.at(i).second << "     "; 
        std::cout << "mass: " << Mass.at(i) << "     "; 
        std::cout << "name/status: " << Names.at(i) << std::endl;
    }
    return 0; 
} 

// save ship manifest to outbound file 
int Ship::create_outbound() {
    std::string filepath = "Outbound/"; 
    char save = 'n';  
    while (save != 'y') {
        std::cout << "Save to: " << filepath << manifest_name << "OUTBOUND.txt" << " y/n: "; 
        std::cin >> save; 
        if (save != 'y') {
            std::cin >> filepath; 
        }
    }
    
    std::ofstream fout(filepath + manifest_name + "OUTBOUND.txt"); 

    if (!fout.is_open()) {
        std::cout << "Unable to open file" << std::endl; 
        return -1; 
    }

    for (int i = 0; i < Coordinates.size(); i++) {
        fout << "["; 
        if (Coordinates.at(i).first < 10) {
            fout << "0"; 
        }
        fout << Coordinates.at(i).first << ",";
        if (Coordinates.at(i).second < 10) {
            fout << "0"; 
        }
        fout << Coordinates.at(i).second << "], "; 

        fout << "{" << Mass.at(i) << "}, ";
        fout << Names.at(i) << std::endl; 
    }

    std::string comment = "Finished a Cycle. Manifest " + manifest_name + "OUTBOUND.txt was written to deskop, and a reminder to operator to send file was displayed."; 
    log_comment(comment); 

    return 0; 
}  

int Ship::log_comment(const std::string &comment) {
    std::string filepath = "logfiles/logfile_";
    time_t now = time(0); 
    tm *ltm = localtime(&now);
    filepath += std::to_string(1900 + ltm->tm_year) + ".txt";  
    
    std::ofstream fout(filepath, std::ios_base::app); 

    if (!fout.is_open()) {
        std::cout << "Unable to open file" << std::endl; 
        return -1; 
    }
    
    fout << 1+ltm->tm_mon << "-" << ltm->tm_mday << "-" << 1900 + ltm->tm_year << ": ";
    fout << ltm->tm_hour << ":" << ltm->tm_min << "  ";
    fout << comment << std::endl;  
    return 0; 
}

int Ship::view_logfile() {
    std::string year; 
    std::cout << "Input year: "; 
    std::cin >> year; 

    std::string filepath = "logfiles/logfile_" + year + ".txt"; 
    std::fstream fin(filepath); 

    if (!fin.is_open()) {
        std::cout << "Error opening file, please try again" << std::endl;
        return -1; 
    }
    std::cout << "Log File " << year << std::endl;
    std::string line; 
    while (getline(fin, line)) {
        std::cout << line << std::endl; 
    }
    std::cout << "End of Log File" << std::endl; 
    return 0; 
} 

std::string Ship::print_ship() const {
    /*
    i = 0 1 2 3 4 5 6 7 
    j = 0 1 2 3 4 5 6 7 8 9 10 11 12
    index = 0 - 95

    */

    std::string ship_view = "";
   
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 12; j++)  {
            // std::cout << Names.at(i*j).size() << " "; 
            
            std::string status; 
            if (i == 0)  {
                status = Names.at(j);      
            }
            else {
                status = Names.at(i*12+j); 
            }
           
            if (status == "UNUSED") {
                ship_view += "|---|";
                std::cout << "|---|";
                //std::cout << "-U-";
                //std::cout << status;
                //std::cout << i << " " << j << std::endl;
            }
            else if (status == "NAN") {
                ship_view += "|NAN|";
                std::cout << "|NAN|";
                //std::cout << "-N-";
                //std::cout << status;
                //std::cout << i << " " << j << std::endl;
            } 
            else {
                ship_view += "|" + status.substr(0, 3) + "|";
                std::cout << "|" + status.substr(0,3) + "|";
                //std::cout << "-X-";
                //std::cout << status.size(); 
                //std::cout << status;
                //std::cout << i << " " << j << std::endl; 
            }
            
        }
        ship_view += "\n";
        std::cout << std::endl; 
    }
    
    return ship_view;
}

double Ship::balance_score() const {

    int right_mass = 0;
    int left_mass = 0; 
    
    for (int i = 0; i < Coordinates.size(); i++) {
        if (Names.at(i) != "NAN" && Names.at(i) != "UNUSED") {
            if (Coordinates.at(i).second <= 6) {
                left_mass+= stoi(Mass.at(i));
            }
            else {
                right_mass += stoi(Mass.at(i)); 
            }
        }
    }

    double balance; 
 
    if (left_mass > right_mass) {
        balance = (right_mass * 1.0) /left_mass;
        
    }
    else {
        balance = (left_mass*1.0)/right_mass; 
    }

    std::cout << "Ship has a balance score of: " << balance << std::endl; 
    std::cout << "right: " << right_mass << std::endl; 
    std::cout << "left: " <<left_mass << std::endl; 
    
    return balance;
}

int Ship::balance_ship() {

    std::vector<std::pair<int, int>> left_items;    // mass values, coord index
    std::vector<std::pair<int, int>> right_items;   // mass values, coord index 
    std::vector<std::pair<int,int>> heavier_side;
    std::vector<int> possible_spaces;          // vector of indices of possible free spaces to move items to 
    std::vector<int> best_index;               // corresponds to heavier_side; stores index from possible_spaces, value at this index in possible_spaces is the best space to move to 
    std::vector<double> best_manhattan;        // corresponds to heavier_side; stores value of best manhattan 
    
    double right_mass = 0; 
    double left_mass = 0; 
    
    // put items into left and right list
    // first is the mass value 
    // second is the coordinate index 
    for (int i = 0; i < Coordinates.size(); i++) {
 
        if (Names.at(i) != "NAN" && Names.at(i) != "UNUSED") {
            if (Coordinates.at(i).second <= 6) {
                left_items.push_back(std::pair<int, int> (stoi(Mass.at(i)), i));
                left_mass+= stoi(Mass.at(i));
            }
            else {
                right_items.push_back(std::pair<int, int> (stoi(Mass.at(i)), i));
                right_mass += stoi(Mass.at(i)); 
            }
        }
    }

     
    if (left_mass > right_mass) {
        heavier_side = left_items; 
    }
    else {
        heavier_side = right_items; 
    }

    print_balance_info(left_items, right_items, left_mass, right_mass); 

    // calculate the possible spaces to place the items 
    calculate_possible_places(possible_spaces, right_mass, left_mass); 

    // calculate best coordinates for heavier side based on the possible spaces and best manhattann  
    calculate_best_manhattan(heavier_side, best_index, best_manhattan, possible_spaces); 

    // calculate which item to sacrifice 
    int sacrifice_index = 0;                // index in the list 
    int best_man = best_manhattan.at(0);  

    // calculates the best place to move 
    // saves index and manhattan 
    calculate_best_place(sacrifice_index, best_man, best_index, best_manhattan, heavier_side); 

    // based on the sacrifice index and best index to move to
    // we swap the mass, names, and update the lists 
    calculate_swap_coordinates(left_mass, right_mass, sacrifice_index, best_index, left_items, right_items); 
    
    
    std::cout << "-----------------UPDATED INFO AFTER MOVING ITEM----------------------------" << std::endl; 
    
    double balance = print_balance_info(left_items, right_items, left_mass, right_mass); 
    
    std::string comment = "Balanced ship. Balance factor is now " + std::to_string(balance); 
    log_comment(comment); 
    return 0; 
    
}

void Ship::calculate_possible_places(std::vector<int> &possible_spaces, int right_mass, int left_mass) {
    
    for (int i = 0; i < Coordinates.size(); i++) {
        if (left_mass > right_mass) {
            if (Names.at(i) == "UNUSED" && Coordinates.at(i).second > 6) {
                // items on first level are fine 
                if (Coordinates.at(i).first == 1) {
                    possible_spaces.push_back(i); 
                }
                // items on upper levels can't be floating 
                // need NAN or some container under it 
                else if (Coordinates.at(i).first > 1 && Names.at(i-12)!= "UNUSED") {
                    possible_spaces.push_back(i); 
                }
            }
        }
        else {
            if (Names.at(i) == "UNUSED" && Coordinates.at(i).second <= 6) {
                if (Coordinates.at(i).first == 1) {
                    possible_spaces.push_back(i); 
                } 
                else if (Coordinates.at(i).first > 1 && Names.at(i-12)!= "UNUSED") {
                    possible_spaces.push_back(i); 
                }
            }
        }
    }
}


void Ship::calculate_best_manhattan(std::vector<std::pair<int,int>> & heavier_side, std::vector<int> & best_index, std::vector<double> &best_manhattan, std::vector<int> &possible_spaces) {
    for (int i = 0; i < heavier_side.size(); i++) {
        // find best coordinate to move to for each item in list 
        // calculate manhattan is overloaded to also take two different coordinate indices 
        // best coordinate can be the same, will use this to help determine which item to move 
        double best_val = calculate_manhattan(heavier_side.at(i).second, possible_spaces.at(0));
        int best_ind = possible_spaces.at(0); 

        for (int j = 0; j < possible_spaces.size(); j++) {
            double temp = calculate_manhattan(heavier_side.at(i).second, possible_spaces.at(j));
            // we want the lowest manhattan distance 
            if (temp < best_val) {
                best_ind = (j);
                best_val = (temp); 
            }
        }
        best_index.push_back(best_ind);
        best_manhattan.push_back(best_val); 
    }
}

double Ship::print_balance_info(std::vector<std::pair<int, int>> &left_side, std::vector<std::pair<int,int>> &right_side, const double &left_mass, const double &right_mass)  {
    double balance, balanceMass, deficit; 

    balanceMass = (left_mass+right_mass)/2.0;
    
    if (left_mass > right_mass) {
        balance = (right_mass * 1.0) /left_mass ;
        deficit = abs(balanceMass - left_mass);
    }
    else {
        balance = (left_mass*1.0)/right_mass; 
        deficit = abs(balanceMass - right_mass);
    }

    sort(left_side.begin(), left_side.begin());
    sort(right_side.begin(), right_side.begin()); 

    std::cout << "balance factor: " << balance << std::endl; 
    std::cout << "balance mass: " << balanceMass << std::endl; 
    std::cout << "deficit: " << deficit << std::endl;
    std::cout << "left mass: " << left_mass << " item mass - "; 
    for (int i = 0; i < left_side.size(); i++) {
        std::cout << left_side.at(i).first << " ";
    }
    std::cout << std::endl; 
    std::cout << "right mass: " << right_mass << " item mass - "; 
    for (int i = 0; i < right_side.size(); i++) {
        std::cout << right_side.at(i).first << " ";
    }
    std::cout << std::endl; 
    return balance; 
}

void Ship::calculate_best_place(int& sacrifice_index, int &best_man, const std::vector<int> &best_index, const std::vector<double> &best_manhattan, const std::vector<std::pair<int,int>> &heavier_side) {
    std::cout << "--------------Calculating best place to move each item----------------" << std::endl; 
    for (int i = 0; i < best_index.size(); i++) {
        if (best_manhattan.at(i) < best_man) {
            best_man = best_manhattan.at(i); 
            sacrifice_index = i; // index can be used to access heavier_side, best_index , and best_manhattan
        }

        // COMMENT OUT LATER, used for testing 
        // original items in heavier side list
        std::cout << "Move item: "; 
        std::cout << Coordinates.at(heavier_side.at(i).second).first <<  ", "; 
        std::cout << Coordinates.at(heavier_side.at(i).second).second << std::endl; 

        // best free place to move and it's manhattan distance to it 
        std::cout << "Move to: "; 
        std::cout << Coordinates.at(best_index.at(i)).first << ", ";
        std::cout << Coordinates.at(best_index.at(i)).second << std::endl; 
        std::cout << "Manhattan: " << best_manhattan.at(i) << std::endl; 
    }
    
    // original items in heavier side 
    std::cout << "---------------------BEST MOVE------------------" << std::endl; 
    std::cout << "Move item: "; 
    std::cout << Coordinates.at(heavier_side.at(sacrifice_index).second).first <<  ", "; 
    std::cout << Coordinates.at(heavier_side.at(sacrifice_index).second).second << std::endl; 
    // find best free place to move and it's manhattan distance to it 
    std::cout << "Move to: "; 
    std::cout << Coordinates.at(best_index.at(sacrifice_index)).first << ", ";
    std::cout << Coordinates.at(best_index.at(sacrifice_index)).second << std::endl; 
    std::cout << "Manhattan: " << best_manhattan.at(sacrifice_index) << std::endl; 
    std::cout << "--------------------END MOVE------------------" << std::endl; 


}

void Ship::calculate_swap_coordinates(double & left_mass, double &right_mass, const int &sacrifice_index, const std::vector<int>&best_index, std::vector<std::pair<int, int>> & left_items, std::vector<std::pair<int, int>> & right_items) {
    if (left_mass > right_mass) {
        // swap the names 
        std::string temp_name = Names.at(best_index.at(sacrifice_index));
        Names.at(best_index.at(sacrifice_index)) = Names.at(left_items.at(sacrifice_index).second); 
        Names.at(left_items.at(sacrifice_index).second) = temp_name; 
        // swap mass 
        std::string temp_mass = Mass.at(best_index.at(sacrifice_index));
        Mass.at(best_index.at(sacrifice_index)) = Mass.at(left_items.at(sacrifice_index).second); 
        Mass.at(left_items.at(sacrifice_index).second) = temp_mass; 

        // update coordinates
        left_items.at(sacrifice_index).second = best_index.at(sacrifice_index); 

        // update left and right mass 
        right_mass += left_items.at(sacrifice_index).first; 
        left_mass -= left_items.at(sacrifice_index).first; 
        
        // add item to right items 
        right_items.push_back(left_items.at(sacrifice_index));

        // get rid of item in left items list 
        left_items.at(left_items.size()-1) = left_items.at(sacrifice_index); 
        left_items.pop_back(); 
    }
    else {
        // swap the names 
        std::string temp_name = Names.at(best_index.at(sacrifice_index));
        Names.at(best_index.at(sacrifice_index)) = Names.at(right_items.at(sacrifice_index).second); 
        Names.at(right_items.at(sacrifice_index).second) = temp_name; 
        
        // swap mass 
        std::string temp_mass = Mass.at(best_index.at(sacrifice_index));
        Mass.at(best_index.at(sacrifice_index)) = Mass.at(right_items.at(sacrifice_index).second); 
        Mass.at(right_items.at(sacrifice_index).second) = temp_mass; 
        
        // update coordinates 
        right_items.at(sacrifice_index).second = best_index.at(sacrifice_index); 

        // update left and right mass 
        left_mass += right_items.at(sacrifice_index).first; 
        right_mass -= right_items.at(sacrifice_index).first; 
        
        // add item to left items 
        left_items.push_back(right_items.at(sacrifice_index));

        // get rid of item in right items list 
        right_items.at(left_items.size()-1) = right_items.at(sacrifice_index); 
        right_items.pop_back(); 
    }
}
// pass in the index to a coordinate 
double Ship::calculate_manhattan(int index_a, int index_b) const {

    return calculate_manhattan(Coordinates.at(index_a).first, Coordinates.at(index_a).second, Coordinates.at(index_b).first, Coordinates.at(index_b).second); 
}  

double Ship::calculate_manhattan(int y_1, int x_1, int y_2, int x_2) const {
    double distance = abs(y_1 - y_2) + abs(x_1-x_2); 
    return distance;
} 

int Ship::load_unload_ship() {
    std::cout << "STUB: load or unload the ship..." << std::endl;
    return 0; // 0 if no error happened
}
