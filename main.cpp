#include <iostream> 
#include "headers/Ship.h" 

// #include "headers/MainWindow.h"

// #include <QApplication>

// int main(int argc, char *argv[])
// {
//     QApplication a(argc, argv);
//     MainWindow w;
//     w.show();
//     return a.exec();
// }

void menu(); 


int main() {
    
   menu(); 

   return 0; 
}

void menu() {
    
    char option;

    Ship Ship1 = Ship();

    while ( !( (option == 'q') && (option == 'Q') ) )  {
        std::cout << "MENU" << std::endl; 

        std::cout << "1: Load Manifest" << std::endl;
        std::cout << "2: Read Manifest (Output to console)" << std::endl; 
        std::cout << "3: Create Outbound Manifest" << std::endl; 
        std::cout << "4: Log comment" << std::endl; 
        std::cout << "5: View logfile" << std::endl; 
        std::cout << "6: Print ship" << std::endl; 
        std::cout << "7: Print balance score" << std::endl; 
        std::cout << "8: Balance ship" << std::endl; 
        std::cout << "q: Quit" << std::endl; 

        std::cin >> option; 
        
        if (option == '1') {
            int test; 
            std::cout << "Test 1-5: ";
            std::cin >> test; 
            std::string testpath = "Manifests/ShipCase" + std::to_string(test) + ".txt";
            Ship1.load_manifest(testpath);
            
        }
        else if (option == '2') {
            if (Ship1.get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl; 
            }
            else {
                Ship1.read_manifest();
            }
            
        }
        else if (option == '3') {
            if (Ship1.get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl; 
            }
            else {
                Ship1.create_outbound();
            }
        }
        else if (option == '4') {
            time_t now = time(0); 
            tm *ltm = localtime(&now);

            std::cout << "Will log to logfile_" << std::to_string(1900 + ltm->tm_year) << ".txt" << std::endl; 
            std::cout << "Single line comment: " << std::endl; 
            std::string comment;
            std::cin.ignore(); 
            getline(std::cin, comment);

            Ship1.log_comment(comment); 
        }
        else if (option == '5') {
            Ship1.view_logfile(); 
        }
        else if (option == '6') {
            if (Ship1.get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl; 
            } else {
                Ship1.print_ship();
            }
        }
        else if (option == '7') {
            if (Ship1.get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl; 
            } else {
                Ship1.balance_score();
            }
        }
        else if (option == '8') {
            if (Ship1.get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl; 
            } else {
                Ship1.balance_ship();
            }
        }
        else if (option == '9') {
            if (Ship1.get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl;
            } else {
                Ship1.load_unload_ship();
            }
        }
        else if ( (option == 'q') || (option == 'Q') ) {
            break; 
        }
        else {
            std::cout << "Error: please use one of the given options." << std::endl;
            continue;
        }

    } 

}