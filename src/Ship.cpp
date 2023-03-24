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
int Ship::load_manifest(const string &filepath) {
    if (manifest_name != "") {
        reset_ship(); 
    }
    
    fstream fin(filepath); 
    
    // save manifest name 
    for (int i = filepath.size()-1; i >=0; i--) {
        if (filepath.at(i) == '/' || filepath.at(i) == '\\') {
            break; 
        } 
        this->manifest_name = filepath.at(i) + this->manifest_name; 
    }
    this->manifest_name = this->manifest_name.substr(0, manifest_name.size()-4); 

    if (!fin.is_open()) {
        cout << "Error opening file, please try again" << endl;
        return -1; 
    }
 
    while(!fin.eof()) {
        string cargo_y; 
        string cargo_x; 
        string cargo_mass;
        string cargo_name;

        getline(fin, cargo_y, ','); 
        getline(fin, cargo_x, ',');
        //cout << cargo_x.substr(0,2) << endl; 
        Coordinates.push_back(pair<int,int> (   stoi(cargo_y.substr(1,2)),  stoi(cargo_x.substr(0,2))   )); 
        getline(fin, cargo_mass, ','); 
        // cout << cargo_mass.substr(2, cargo_mass.length()-3) << endl;
        Mass.push_back(cargo_mass.substr(2, cargo_mass.length()-3)); 
        
        getline(fin, cargo_name);  
        if (fin.eof()) {
            Names.push_back(cargo_name.substr(1, cargo_name.length()-1)); 
            break; 
        }
        else {
            Names.push_back(cargo_name.substr(1, cargo_name.length()-2)); 
        }
       
    }
    
    fin.close(); 

    string comment = "Uploaded Manifest " + manifest_name + ".txt"; 
    log_comment(comment); 

    return 0; 
}
// output manifest contents to console 
int Ship::read_manifest() {
    cout << "Manifest" << endl; 
    for (int i = 0 ; i < Coordinates.size(); i++) {
        cout << "coordinates: ";
        if (Coordinates.at(i).first < 10) {
            cout << " "; 
        }
        cout << Coordinates.at(i).first << ", ";
        if (Coordinates.at(i).second < 10) {
            cout << " "; 
        }
        cout << Coordinates.at(i).second << "     "; 
        cout << "mass: " << Mass.at(i) << "     "; 
        cout << "name/status: " << Names.at(i) << endl;
    }
    return 0; 
} 

// save ship manifest to outbound file 
int Ship::create_outbound() {
    string filepath = "Outbound/"; 
    char save = 'n';  
    while (save != 'y') {
        cout << "Save to: " << filepath << manifest_name << "OUTBOUND.txt" << " y/n: "; 
        cin >> save; 
        if (save != 'y') {
            cin >> filepath; 
        }
    }
    
    ofstream fout(filepath + manifest_name + "OUTBOUND.txt"); 

    if (!fout.is_open()) {
        cout << "Unable to open file" << endl; 
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
        fout << Names.at(i) << endl; 
    }

    string comment = "Finished a Cycle. Manifest " + manifest_name + "OUTBOUND.txt was written to deskop, and a reminder to operator to send file was displayed."; 
    log_comment(comment); 

    return 0; 
}  

int Ship::log_comment(const string &comment) {
    string filepath = "logfiles/logfile_";
    time_t now = time(0); 
    tm *ltm = localtime(&now);
    filepath += to_string(1900 + ltm->tm_year) + ".txt";  
    
    ofstream fout(filepath, ios_base::app); 

    if (!fout.is_open()) {
        cout << "Unable to open file" << endl; 
        return -1; 
    }
    
    fout << 1+ltm->tm_mon << "-" << ltm->tm_mday << "-" << 1900 + ltm->tm_year << ": ";
    fout << ltm->tm_hour << ":" << ltm->tm_min << "  ";
    fout << comment << endl;  
    return 0; 
}

int Ship::view_logfile() {
    string year; 
    cout << "Input year: "; 
    cin >> year; 

    string filepath = "logfiles/logfile_" + year + ".txt"; 
    fstream fin(filepath); 

    if (!fin.is_open()) {
        cout << "Error opening file, please try again" << endl;
        return -1; 
    }
    cout << "Log File " << year << endl;
    string line; 
    while (getline(fin, line)) {
        cout << line << endl; 
    }
    cout << "End of Log File" << endl; 
    return 0; 
} 

int Ship::print_ship() const {
    /*
    i = 0 1 2 3 4 5 6 7 
    j = 0 1 2 3 4 5 6 7 8 9 10 11 12
    index = 0-95

    */
   
    for (int i = 7; i >= 0; i--) {
        for (int j = 0; j < 12; j++)  {
            //cout << Names.at(i*j).size() << " "; 
            
            string status; 
            if (i == 0)  {
                status = Names.at(j);      
            }
            else {
                status = Names.at(i*12+j); 
            }
           
            if (status == "UNUSED") {
                cout << "-U-";
                //cout << status;
                //cout << i << " " << j << endl;
            }
            else if (status == "NAN") {
                cout << "-N-";
                //cout << status;
                //cout << i << " " << j << endl;
            } 
            else {
                cout << "-X-";
                //cout << status.size(); 
                //cout << status;
                //cout << i << " " << j << endl; 
            }
            
        }
        cout << endl; 
    }
    
    return 0;
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

    cout << "Ship has a balance score of: " << balance << endl; 
    cout << "right: " << right_mass << endl; 
    cout << "left: " <<left_mass << endl; 
    
    return balance;
}


int Ship::balance_ship() {

    vector<pair<int, int>> left_items;    // mass values, coord index
    vector<pair<int, int>> right_items;   // mass values, coord index 
    
    int right_mass = 0; 
    int left_mass = 0; 
    double deficit; 
    double balance;
    double balanceMass;
    // put items into left and right list
    // first is the mass value 
    // second is the coordinate index 
    for (int i = 0; i < Coordinates.size(); i++) {
 
        if (Names.at(i) != "NAN" && Names.at(i) != "UNUSED") {
            if (Coordinates.at(i).second <= 6) {
                left_items.push_back(pair<int, int> (stoi(Mass.at(i)), i));
                left_mass+= stoi(Mass.at(i));
            }
            else {
                right_items.push_back(pair<int, int> (stoi(Mass.at(i)), i));
                right_mass += stoi(Mass.at(i)); 
            }
        }
    }

    balanceMass = (left_mass+right_mass)/2.0;
    
    if (left_mass > right_mass) {
        balance = (right_mass * 1.0) /left_mass ;
        deficit = abs(balanceMass - left_mass);
    }
    else {
        balance = (left_mass*1.0)/right_mass; 
        deficit = abs(balanceMass - right_mass);
    }

     // ------------------------------------------------------------------------
    // sort left and right vectors + coordinates
    sort(left_items.begin(), left_items.begin());
    sort(right_items.begin(), right_items.begin()); 

    cout << "balance factor: " << balance << endl; 
    cout << "balance mass: " << balanceMass << endl; 
    cout << "deficit: " << deficit << endl;
    cout << "left mass: " << left_mass << " item mass - "; 
    for (int i = 0; i < left_items.size(); i++) {
        cout << left_items.at(i).first << " ";
    }
    cout << endl; 
    cout << "right mass: " << right_mass << " item mass - "; 
    for (int i = 0; i < right_items.size(); i++) {
        cout << right_items.at(i).first << " ";
    }
    cout << endl; 
    // ------------------------------------------------------------------------
    // calculate the possible spaces to place the items 
    vector<int> possible_spaces; // vector of indices of possible spaces to move items to 
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
    // ------------------------------------------------------------------------

    vector<pair<int,int>> heavier_side; 
    if (left_mass > right_mass) {
        heavier_side = left_items; 
    }
    else {
        heavier_side = right_items; 
    }
    

    vector<int> best_index; // should end up having the same size as heavier_side list 
    vector<double> best_manhattan; 
   
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


    // calculate which item to sacrifice 
    int sacrifice_index = 0;                // index in the list 
    int best_man = best_manhattan.at(0);  

    cout << "--------------Calculating best place to move each item----------------" << endl; 
    for (int i = 0; i < best_index.size(); i++) {
        if (best_manhattan.at(i) < best_man) {
            best_man = best_manhattan.at(i); 
            sacrifice_index = i; // index can be used to access heavier_side, best_index , and best_manhattan
        }

        // COMMENT OUT LATER, used for testing 
        // original items in heavier side list
        cout << "Move item: "; 
        cout << Coordinates.at(heavier_side.at(i).second).first <<  ", "; 
        cout << Coordinates.at(heavier_side.at(i).second).second << endl; 

        // best free place to move and it's manhattan distance to it 
        cout << "Move to: "; 
        cout << Coordinates.at(best_index.at(i)).first << ", ";
        cout << Coordinates.at(best_index.at(i)).second << endl; 
        cout << "Manhattan: " << best_manhattan.at(i) << endl; 
    }
    
    // original items in heavier side 
    cout << "---------------------BEST MOVE------------------" << endl; 
    cout << "Move item: "; 
    cout << Coordinates.at(heavier_side.at(sacrifice_index).second).first <<  ", "; 
    cout << Coordinates.at(heavier_side.at(sacrifice_index).second).second << endl; 
    // find best free place to move and it's manhattan distance to it 
    cout << "Move to: "; 
    cout << Coordinates.at(best_index.at(sacrifice_index)).first << ", ";
    cout << Coordinates.at(best_index.at(sacrifice_index)).second << endl; 
    cout << "Manhattan: " << best_manhattan.at(sacrifice_index) << endl; 
    cout << "--------------------END MOVE------------------" << endl; 

    if (left_mass > right_mass) {
        // swap the names 
        string temp_name = Names.at(best_index.at(sacrifice_index));
        Names.at(best_index.at(sacrifice_index)) = Names.at(left_items.at(sacrifice_index).second); 
        Names.at(left_items.at(sacrifice_index).second) = temp_name; 
        // swap mass 
        string temp_mass = Mass.at(best_index.at(sacrifice_index));
        Mass.at(best_index.at(sacrifice_index)) = Names.at(left_items.at(sacrifice_index).second); 
        Mass.at(left_items.at(sacrifice_index).second) = temp_name; 

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
        string temp_name = Names.at(best_index.at(sacrifice_index));
        Names.at(best_index.at(sacrifice_index)) = Names.at(right_items.at(sacrifice_index).second); 
        Names.at(right_items.at(sacrifice_index).second) = temp_name; 
        
        // swap mass 
        string temp_mass = Mass.at(best_index.at(sacrifice_index));
        Mass.at(best_index.at(sacrifice_index)) = Names.at(right_items.at(sacrifice_index).second); 
        Mass.at(right_items.at(sacrifice_index).second) = temp_name; 
        
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
    
    cout << "-----------------UPDATED INFO AFTER MOVING ITEM----------------------------" << endl; 
    
    // sort left and right vectors + coordinates
    sort(left_items.begin(), left_items.begin());
    sort(right_items.begin(), right_items.begin()); 

    cout << "balance factor: " << balance << endl; 
    cout << "balance mass: " << balanceMass << endl; 
    cout << "deficit: " << deficit << endl;
    cout << "left mass: " << left_mass << " item mass - "; 
    for (int i = 0; i < left_items.size(); i++) {
        cout << left_items.at(i).first << " ";
    }
    cout << endl; 
    cout << "right mass: " << right_mass << " item mass - "; 
    for (int i = 0; i < right_items.size(); i++) {
        cout << right_items.at(i).first << " ";
    }
    cout << endl; 

    
    return 0; 
    
}

// pass in the index to a coordinate 
double Ship::calculate_manhattan(int index_a, int index_b) const {

    return calculate_manhattan(Coordinates.at(index_a).first, Coordinates.at(index_a).second, Coordinates.at(index_b).first, Coordinates.at(index_b).second); 
}  

double Ship::calculate_manhattan(int y_1, int x_1, int y_2, int x_2) const {
    double distance = abs(y_1 - y_2) + abs(x_1-x_2); 
    return distance;
} 