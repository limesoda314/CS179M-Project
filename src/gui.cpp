// To run: g++ src/gui.cpp -lncurses 
// must install: sudo apt install libncurses5-dev libncursesw5-dev


#include <ncurses.h> 
#include <iostream> 
#include "../headers/Ship.h"
#include <string> 
using namespace std;

void menu(); 

int main(int argc, char ** argv)
{
    // init screen and sets up screen
    initscr();

    // print to screen

    // refreshes the screen
    
    menu(); 

    // pause the screen output
    

    // deallocates memory and ends ncurses
    endwin();
    return 0;
}

void menu() {

    WINDOW *menu_win;
    
    menu_win = newwin(30, 10, (80-30)/2, (24-10)/2);
    noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
    
    int option = 0;
    Ship Ship1 = Ship();
    
    int row = 1;
    int col = 10; 

    // char *Options[] = {};   
    vector<string> Options = {
        "1: Load Manifest",
        "2: Read Manifest (Output to console)",
        "3: Create Outbound Manifest",
        "4: Log comment",
        "5: View logfile",
        "6: Print ship",
        "7: Print balance score",
        "8: Balance ship",
        "9: Quit"
    }; 

    while (1) {
        clear(); 
        row = 1; 
        col = 10; 
        mvprintw(0, 5, "-------MENU------"); 
        for (int i = 0; i < 9; i++) {
            mvprintw(row+i, col, "%s\n", Options.at(i).c_str()); 
        }

        char option = getch();
        // getline ?? getnstr( users_name, sizeof( users_name ) - 1 );
        
         
  
        if (option == '1') {
            clear(); 
            char test; 
            row = 0; 
            col = 10; 
            while (1) {
                refresh(); 
                mvprintw(row, col/2,  "Load Manifest: ");
                mvprintw(row+1, col,  "Test 1-5: ");
                test = wgetch();  
                
                if (test == '1') {
                    string testpath = "Manifests/ShipCase";
                    testpath.push_back(test);
                    testpath += ".txt"; 
                    Ship1.load_manifest(testpath);
                    mvprintw(row+5, col,  "Loaded Manifest %s", testpath.c_str());
                    mvprintw(row+6, col,  "Returning to menu");
                    break; 
                }
                else {
                    mvprintw(row+6, col,  "Returning to menu");
                }
            }
            
        }

        // if (option == 2) {
        //     if (Ship1.get_manifest_name() == "") {
        //         cout << "Load a manifest first" << endl; 
        //     }
        //     else {
        //         Ship1.read_manifest();
        //     }
            
        // }

        // if (option == 3) {
        //     if (Ship1.get_manifest_name() == "") {
        //         cout << "Load a manifest first" << endl; 
        //     }
        //     else {
        //         Ship1.create_outbound();
        //     }
        // }
        // if (option == 4) {
        //     time_t now = time(0); 
        //     tm *ltm = localtime(&now);
            

        //     cout << "Will log to logfile_" << to_string(1900 + ltm->tm_year) << ".txt" << endl; 
        //     cout << "Single line comment: " << endl; 
        //     string comment;
        //     cin.ignore(); 
        //     getline(cin, comment);

        //     Ship1.log_comment(comment); 
        // }
        // if (option == 5) {
        //     Ship1.view_logfile(); 
        // }
        // if (option == 6) {
        //     if (Ship1.get_manifest_name() == "") {
        //         cout << "Load a manifest first" << endl; 
        //     } else {
        //         Ship1.print_ship();
        //     }
            
        // }
        // if (option == 7) {
        //     if (Ship1.get_manifest_name() == "") {
        //         cout << "Load a manifest first" << endl; 
        //     } else {
                 
        //         Ship1.balance_score();
                
        //     }
        // }
        // if (option == 8) {
        //     if (Ship1.get_manifest_name() == "") {
        //         cout << "Load a manifest first" << endl; 
        //     } else {
                
        //         Ship1.balance_ship();
                 
        //     }
        // }

        if (option == 9) {
            break; 
        }

    } 

}
