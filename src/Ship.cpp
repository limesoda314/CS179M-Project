#include "../headers/Ship.h"

// load manifest from filepath
int Ship::load_manifest(const string &filepath) {
    
    fstream fin(filepath); 
    
    // save manifest name 
    for (int i = filepath.size()-1; i >=0; i--) {
        if (filepath.at(i) == '/' || filepath.at(i) == '\\') {
            break; 
        } 
        this->manifest_name = filepath.at(i) + this->manifest_name; 
    }

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
        // cout << cargo_name.substr(1, cargo_name.length()-1) << endl; 
        Names.push_back(cargo_name.substr(1, cargo_name.length()-1)); 
    }
    
    fin.close(); 

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
        cout << "Save to: " << filepath << manifest_name << " y/n: "; 
        cin >> save; 
        if (save != 'y') {
            cin >> filepath; 
        }
    }
    
    ofstream fout(filepath + manifest_name); 

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

    return 0; 
}  
