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
    double right =0; 
    double left=0; 
    
    for (int i = 0; i < Coordinates.size(); i++) {
        if (Names.at(i) != "NAN" && Names.at(i) != "UNUSED") {
            if (Coordinates.at(i).second <= 6) {
                left++;
            }
            else {
                right++; 
            }
        }
    }
    cout << endl; 
    cout << "right: " << right << endl; 
    cout << "left: " <<left << endl; 
    double balance; 
    if (left > right) {
        balance = right/left;
    }
    else {
        balance = left/right; 
    } 
    return balance;
}