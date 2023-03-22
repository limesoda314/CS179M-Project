#include <iostream> 
#include <fstream> 
#include <vector> 
using namespace std; 

// given the filepath, we read and load the contents of the manifest; return 0 if successful, return -1 if unsuccessful 
int load_manifest(const string &filepath, vector<pair<int,int>> &coordinates, vector<string> &mass, vector<string> &name); 

// output the contents of the manifest (development only)
int read_manifest(vector<pair<int,int>> &coordinates, vector<string> &mass, vector<string> &name); 

// create the updated manifest and save it as [manifest name]OUTBOUND.txt
int create_outbound_manifest(string &filepath, vector<pair<int,int>> &coordinates, vector<string> &mass, vector<string> &name); 
 
// write comment to logfile; return 0 if successful, return -1 if unsuccessful 
int write_log(string comment); 

// read contents of logfile; return 0 if successful, return -1 if unsuccessful 
int view_log(); 



int main() {
    vector<pair<int, int>> coordinates; // y,x 
    vector<string> mass; 
    vector<string> name; 

    // string filepath; 
    // cout << "manifest filepath: " << endl; 
    // cin >> filepath; 

    int test; 
    string filepath; 
    cout << "Test 1-5: "; 
    cin >> test;
    filepath = "Manifests/ShipCase" + to_string(test) + ".txt"; 

    // if it fails, keep asking for filepath 
    while (load_manifest(filepath, coordinates, mass, name)) {
        // cout << "manifest filepath: " << endl; 
        // cin >> filepath; 
      
        cout << "Test 1-5"; 
        cin >> test; 
        filepath = "Manifests/ShipCase" + to_string(test) + ".txt"; 
    } 

    cout << "Manifest loaded" << endl;
    // read_manifest(coordinates, mass, name); 

    string outbound_filepath; 
    for (int i = filepath.size()-1; i >=0; i--) {
        if (filepath.at(i) == '/' || filepath.at(i) == '\\') {
            break; 
        } 
        outbound_filepath = filepath.at(i) + outbound_filepath; 
    }

    string outbound_directory; 
    char save = 'n'; 
    while (save != 'y') {
        cout << "Manifest will be saved as " << outbound_filepath << endl; 
        cout << "Please specify what directory to save the file: "; 
        cin >> outbound_directory; 
        cout << "save to: " << outbound_directory << outbound_filepath << " y/n: "; 
        cin >> save; 
    }
    outbound_filepath = outbound_directory + outbound_filepath; 
    create_outbound_manifest(outbound_filepath, coordinates, mass, name);  
    
    

    return 0; 
}

int load_manifest(const string &filepath, vector<pair<int,int>> &coordinates, vector<string> &mass, vector<string> &name) {

    fstream fin(filepath); 

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
        coordinates.push_back(pair<int,int> (   stoi(cargo_y.substr(1,2)),  stoi(cargo_x.substr(0,2))   )); 
        getline(fin, cargo_mass, ','); 
        // cout << cargo_mass.substr(2, cargo_mass.length()-3) << endl;
        mass.push_back(cargo_mass.substr(2, cargo_mass.length()-3)); 
        getline(fin, cargo_name);  
        // cout << cargo_name.substr(1, cargo_name.length()-1) << endl; 
        name.push_back(cargo_name.substr(1, cargo_name.length()-1)); 
    }
    
    fin.close(); 

    return 0; 
}

int read_manifest(vector<pair<int,int>> &coordinates, vector<string> &mass, vector<string> &name) {
    
    if (coordinates.size() != mass.size() && mass.size() != name.size()){
        cout << "failed to read manifest correctly" << endl; 
        return -1; 
    }
    cout << "Manifest" << endl; 
    for (int i = 0 ; i < coordinates.size(); i++) {
        cout << "coordinates: ";
        if (coordinates.at(i).first < 10) {
            cout << " "; 
        }
        cout << coordinates.at(i).first << ", ";
        if (coordinates.at(i).second < 10) {
            cout << " "; 
        }
        cout << coordinates.at(i).second << "     "; 
        cout << "mass: " << mass.at(i) << "     "; 
        cout << "name/status: " << name.at(i) << endl;
    }

    return 0; 
}

int create_outbound_manifest(string &filepath, vector<pair<int,int>> &coordinates, vector<string> &mass, vector<string> &name) {
    ofstream fout(filepath); 

    if (!fout.is_open()) {
        cout << "Unable to open file" << endl; 
        return -1; 
    }

    for (int i = 0; i < coordinates.size(); i++) {
        fout << "["; 
        if (coordinates.at(i).first < 10) {
            fout << "0"; 
        }
        fout << coordinates.at(i).first << ",";
        if (coordinates.at(i).second < 10) {
            fout << "0"; 
        }
        fout << coordinates.at(i).second << "], "; 

        fout << "{" << mass.at(i) << "}, ";
        fout << name.at(i) << endl; 
    }

    return 0; 
    
}

// int write_log(string comment) {
    

// }