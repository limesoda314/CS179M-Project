#include <iostream> 
#include "headers/Ship.h" 

#include "headers/MainWindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

void menu(); 


//int main() {
    
//    menu(); 

//    return 0; 
//}

void menu() {
    
    char option;

    Ship Ship1 = Ship();

    while ( !( (option == 'q') && (option == 'Q') ) )  {
        cout << "MENU" << endl; 

        cout << "1: Load Manifest" << endl;
        cout << "2: Read Manifest (Output to console)" << endl; 
        cout << "3: Create Outbound Manifest" << endl; 
        cout << "4: Log comment" << endl; 
        cout << "5: View logfile" << endl; 
        cout << "6: Print ship" << endl; 
        cout << "7: Print balance score" << endl; 
        cout << "8: Balance ship" << endl; 
        cout << "q: Quit" << endl; 

        cin >> option; 
        
        if (option == '1') {
            int test; 
            cout << "Test 1-5: ";
            cin >> test; 
            string testpath = "Manifests/ShipCase" + to_string(test) + ".txt";
            Ship1.load_manifest(testpath);
            
        }
        else if (option == '2') {
            if (Ship1.get_manifest_name() == "") {
                cout << "Load a manifest first" << endl; 
            }
            else {
                Ship1.read_manifest();
            }
            
        }
        else if (option == '3') {
            if (Ship1.get_manifest_name() == "") {
                cout << "Load a manifest first" << endl; 
            }
            else {
                Ship1.create_outbound();
            }
        }
        else if (option == '4') {
            time_t now = time(0); 
            tm *ltm = localtime(&now);

            cout << "Will log to logfile_" << to_string(1900 + ltm->tm_year) << ".txt" << endl; 
            cout << "Single line comment: " << endl; 
            string comment;
            cin.ignore(); 
            getline(cin, comment);

            Ship1.log_comment(comment); 
        }
        else if (option == '5') {
            Ship1.view_logfile(); 
        }
        else if (option == '6') {
            if (Ship1.get_manifest_name() == "") {
                cout << "Load a manifest first" << endl; 
            } else {
                Ship1.print_ship();
            }
        }
        else if (option == '7') {
            if (Ship1.get_manifest_name() == "") {
                cout << "Load a manifest first" << endl; 
            } else {
                Ship1.balance_score();
            }
        }
        else if (option == '8') {
            if (Ship1.get_manifest_name() == "") {
                cout << "Load a manifest first" << endl; 
            } else {
                Ship1.balance_ship();
            }
        }
        else if (option == '9') {
            if (Ship1.get_manifest_name() == "") {
                cout << "Load a manifest first" << endl;
            } else {
                Ship1.load_unload_ship();
            }
        }
        else if ( (option == 'q') || (option == 'Q') ) {
            break; 
        }
        else {
            cout << "Error: please use one of the given options." << endl;
            continue;
        }

    } 

}