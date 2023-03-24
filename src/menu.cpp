// Modified code from: https://tldp.org/HOWTO/NCURSES-Programming-HOWTO/keys.html
#include <ncurses.h>
#include <string>
#include <iostream>
#include <vector> 
#include "../headers/Ship.h"

#define WIDTH 40
#define HEIGHT 15 

int startx = 0;
int starty = 0;

vector<string> choices =  {
	"1: Load Manifest",
	"2: Read Manifest",
	"3: Create Outbound Manifest",
	"4: Log comment",
	"5: View logfile",
	"6: Print ship",
	"7: Print balance score",
	"8: Balance ship",
	"9: EXIT"
};

int n_choices = choices.size(); 
void print_menu(WINDOW *menu_win, int highlight);
void menu_operation(WINDOW *option_win, int option, Ship &); 
int main(){	
	WINDOW *menu_win;
	int highlight = 1;
	int choice = 0;
	int c;
	Ship Ship1 = Ship();

	initscr();
	clear();
	noecho();
	cbreak();	/* Line buffering disabled. pass on everything */
	startx = (80 - WIDTH) / 2;
	starty = (24 - HEIGHT) / 2;
		
	menu_win = newwin(HEIGHT, WIDTH, starty, startx);
	keypad(menu_win, TRUE);
	mvprintw(0, 0, "Use arrow keys to go up and down, Press enter to select a choice");
	refresh();
	print_menu(menu_win, highlight);
	while(1)
	{	c = wgetch(menu_win);
		switch(c)
		{	case KEY_UP:
				if(highlight == 1)
					highlight = n_choices;
				else
					--highlight;
				break;
			case KEY_DOWN:
				if(highlight == n_choices)
					highlight = 1;
				else 
					++highlight;
				break;
			case 10:
				choice = highlight;
				menu_operation(menu_win, highlight + '0', Ship1);
				break;
			
			case '9': 
				endwin(); 
				return 0; 
			default:
				if (c >= '1' || c <= '9') {
					clear(); 
					menu_operation(menu_win, c, Ship1); 
				}
				else {
					mvprintw(24, 0, "Charcter pressed is = %3d Hopefully it can be printed as '%c' ", c, c);
				}
				refresh();
				break;
		}
		print_menu(menu_win, highlight);
		if(choice != 0)	/* User did a choice come out of the infinite loop */
			break;
	}	
	mvprintw(23, 0, "You chose choice %d with choice string %s\n", choice, choices[choice - 1].c_str());
	clrtoeol();
	refresh();
	endwin();
	return 0;
}


void print_menu(WINDOW *menu_win, int highlight) {
	int x, y, i;	

	x = 2;
	y = 2;
	box(menu_win, 0, 0);
	for(i = 0; i < n_choices; ++i)
	{	if(highlight == i + 1) /* High light the present choice */
		{	wattron(menu_win, A_REVERSE); 
			mvwprintw(menu_win, y, x, "%s", choices.at(i).c_str());
			wattroff(menu_win, A_REVERSE);
		}
		else
			mvwprintw(menu_win, y, x, "%s", choices.at(i).c_str());
		++y;
	}
	wrefresh(menu_win);
}

void menu_operation(WINDOW *menu_win,int option, Ship &Ship1) {
	if (option == '1') {
		clear(); 
		char test; 
		int row = 0; 
		int col = 10; 
		while (1) {
			refresh(); 
			
			mvprintw(row, col/2,  "Load Manifest: ");
			mvprintw(row+1, col,  "Test 1-5: ");
			test = getch();  
			
			if (test >= '1' && test <= '5') {
				string testpath = "Manifests/ShipCase";
				testpath.push_back(test);
				testpath += ".txt"; 
				Ship1.load_manifest(testpath);
				mvprintw(row+5, col,  "Loaded Manifest %s", testpath.c_str());
				mvprintw(row+6, col,  "Returning to menu");
				napms(200);
				break; 
			}
			else {
				mvprintw(row+5, col,  "Please type a value 1-5. q to go back");
				while (1){
					char key_press = getch();

					if (key_press == 'q'){
						break;
					}
				}
			}
		}
		
	}
}