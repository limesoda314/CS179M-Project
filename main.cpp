#include <iostream> 
#include "headers/Ship.h" 


void menu(); 


int main() {
    

    menu(); 

    return 0; 
}

void menu() {
    Ship Ship1 = Ship(); 

    int test; 
    cout << "Test 1-5: ";
    cin >> test; 
    string testpath = "Manifests/ShipCase" + to_string(test) + ".txt"; 
    Ship1.load_manifest(testpath); 
    Ship1.read_manifest(); 
    Ship1.create_outbound(); 
    
    cout << "finished" << endl; 

}