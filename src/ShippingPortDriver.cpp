#include "../headers/ShippingPortDriver.h"
#include "../headers/Ship.h"
#include "../headers/MainWindow.h"

ShippingPortDriver::ShippingPortDriver() {
    this->count = 0;
    this->ship = new Ship();
}

/* Can run AStar and Uniform Cost Search */
ShipState* ShippingPortDriver::graphSearch(ShipState* problem) {

    std::cout << "             Beginning graph search" << std::endl;

    // std::cout << "              > frontier push" << std::endl;
    // Initialize the frontier using the initial state of problem
    this->frontier.push(problem);
    this->frontier_set.insert(problem);

    // std::cout << "              > frontier size check" << std::endl;
    // Tracking max frontier length
    // if (this->frontier.size() > this->maxFrontierLength) {
    //     this->maxFrontierLength = this->frontier.size();
    // }

    // loop do
    // std::cout << "              > starting search" << std::endl;
    while (true) {

        // If frontier is empty, then return failure
        if (this->frontier.size() == 0) { return nullptr; }

        // std::cout << "                  > getting leaf" << std::endl;
        // Pick the smallest leaf, based on algorithm
        ShipState* leaf = this->frontier.top();

        // std::cout << "                  > popping from frontier" << std::endl;
        this->frontier.pop();

        // std::cout << "                  > erasing from frontier" << std::endl;
        this->frontier_set.erase(leaf);

        // std::cout << "                  > calculating balance factor" << std::endl;
        // If leaf is the goal, return it
        if (leaf->balanceFactor() >= 0.9 && leaf->balanceFactor() <= 1.1) {
            return leaf;
        }

        // std::cout << "                  > adding to explored" << std::endl;
        // Add to explored set if not
        this->explored.insert(leaf);

        // If not in explored, expand
        // std::cout << "==============================================================\n Current expanding node with g(n) = "
                //   << leaf->getCost() << ", h(n) = " << leaf->heuristic() << ", and f(n) = " << leaf->f_valueFrom() << "\n";

        // std::cout << "                  > drawing current state" << std::endl;
//        leaf->draw(std::cout);

        // std::cout << "                  > expanding state..." << std::endl;

        if (
            (this->frontier_set.find(leaf) == this->frontier_set.end())
//            (this->frontier_set.find(leaf) == this->frontier_set.end())
        ) {
            leaf->expandNode();
        }

        this->count++;

        // std::cout << "Expanding node " << this->count << "...\n";
        // std::cout << "Size: " << this->frontier_set.size() << "\n\n";

        // std::cout << "                  > add all the children to the frontier..." << std::endl;
        // Add the children to the frontier if not there or in explored
        for (int i = 0; i < leaf->getChildrenLength(); i++) {

            // Child is not in frontier

            // std::cout << "                  > check if leaf child(i) is in frontier" << std::endl;
            bool in_frontier = ( this->frontier_set.find(leaf->getChild(i)) != this->frontier_set.end() );

            // Child is not in explored
            // std::cout << "                  > check if leaf chisld(i) is in explored" << std::endl;
            bool in_explored = ( this->explored.find(leaf->getChild(i)) != this->explored.end() );

            // If both conditions are met, push into frontier
            // std::cout << "                  > if both conditions are met, push into frontier" << std::endl;
            if ( !in_frontier && !in_explored ) {

                // std::cout << "                      > pushing..." << std::endl;
                this->frontier.push( leaf->getChild(i) );

                // std::cout << "                      > adding to set" << std::endl;
                this->frontier_set.insert( leaf->getChild(i) );

            }

        }

    }

}

int ShippingPortDriver::QTGUI(int argc, char** argv) {
    QApplication app (argc, argv);
    MainWindow myMainWindow;
    myMainWindow.show();
    return app.exec();
}

void ShippingPortDriver::setShip(Ship* newShip) {
    this->ship = newShip;
}

void ShippingPortDriver::menu() {
    char option = 'l'; // l means nothing

    this->ship = new Ship();

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
            this->ship->load_manifest(testpath);

        }
        else if (option == '2') {
            if (this->ship->get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl;
            }
            else {
                this->ship->read_manifest();
            }
        }
        else if (option == '3') {
            if (this->ship->get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl;
            }
            else {
                this->ship->create_outbound();
            }
        }
        else if (option == '4') {
            time_t now = std::time(0);
            tm *ltm = std::localtime(&now);

            std::cout << "Will log to logfile_" << std::to_string(1900 + ltm->tm_year) << ".txt" << std::endl;
            std::cout << "Single line comment: " << std::endl;
            std::string comment;
            std::cin.ignore();
            std::getline(std::cin, comment);

            this->ship->log_comment(comment);
        }
        else if (option == '5') {
            this->ship->view_logfile();
        }
        else if (option == '6') {
            if (this->ship->get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl;
            } else {
                this->ship->print_ship();
            }
        }
        else if (option == '7') {
            if (this->ship->get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl;
            } else {
                this->ship->balance_score();
            }
        }
        else if (option == '8') {
            if (this->ship->get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl;
            } else {
                std::vector<std::pair<int, int>> return_vector;

                this->balance_ship(return_vector);

                std::cout << "printing from the GUI" << std::endl;

                std::cout << "{ ";
                for (int i = 0; i < return_vector.size(); i++) {
                    std::cout << "(" << return_vector.at(i).first << ","
                              << return_vector.at(i).second << "), ";
                }
                std::cout << " }" << std::endl;
            }
        }
        else if (option == '9') {
            if (this->ship->get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl;
            } else {
                this->ship->load_unload_ship();
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

void ShippingPortDriver::printPath(std::ostream& out, ShipState* leaf, int i) {
    // std::cout << "Printing the path..." << std::endl;
    if (!leaf) {
        // std::cout << "reached above root..." << std::endl;
        return;
    }

    // std::cout << "printing current" << std::endl;

    printPath(out, leaf->getParent(), i + 1);

//    this->ship->print_ship();

    leaf->drawFree(std::cout << "   ");
    leaf->drawMoves(std::cout << "   ");
    leaf->draw(std::cout << "   ");

    if (leaf->getParent()) {
        leaf->drawChange(out, this->balance_list);
    }
    // out << i << ")\n";

}

void ShippingPortDriver::defaultTest() {

    ShipState* startState = new ShipState(
        this->ship->getCoords(),
        this->ship->getMasses(),
        this->ship->getNames(),
        new BalanceFactorHeuristic(),
        nullptr
    );

    // Graph search algorith
    ShipState* solution = this->graphSearch(startState);
    if (solution != nullptr) {
        std::cout << "Goal!!!" << std::endl;
        solution->draw(std::cout);
        std::cout << "\n";
        this->printPath(std::cout, solution, 0);
    }
    else {
        std::cout << "Failure!!!\n\n"
                  << "No answer was found. :(" << std::endl;
    }

}

void ShippingPortDriver::balance_ship(
    std::vector<std::pair<int, int>>& send_back
)
{
    this->balance_list.clear();

    std::cout << "[4] curr size of balanced_list: " << send_back.size() << std::endl;

    std::cout << "Attempting to balance ship. Loading..." << std::endl;

    std::cout << " > Creating starting ship state" << std::endl;
    ShipState* startState = new ShipState(
        this->ship->getCoords(),
        this->ship->getMasses(),
        this->ship->getNames(),
        new BalanceFactorHeuristic(),
        nullptr
    );

    this->startState = startState; // set the pointer, will be useful for output and deallocation

    std::cout << "getting information for debugging" << std::endl;
    startState->draw(std::cout      << "    - ");
    startState->drawFree(std::cout  << "    - ");
    startState->drawMoves(std::cout << "    - ");

    // print out getNames from ship
    std::cout << "  Drawing ship->getNames: {";
    for (int i = 0; i < this->ship->getNames().size(); i++) {
        std::cout << "\"" << this->ship->getNames().at(i) << ", ";
    }
    std::cout << "}" << std::endl;

    std::cout << "[5] curr size of balanced_list: " << send_back.size() << std::endl;

    std::cout << " > curr balance factor: " << startState->balanceFactor() << std::endl;

    std::cout << " > Creating solution (may take a while)..." << std::endl;

    std::cout << "[6] curr size of balanced_list: " << send_back.size() << std::endl;
    ShipState* solution;
    if (startState->balanceFactor() >= 0.9 && startState->balanceFactor() <= 1.1) {
        solution = startState;
    }
    else {
        solution = this->graphSearch(startState);
    }

    std::cout << "[7] curr size of balanced_list: " << send_back.size() << std::endl;

    std::cout << "   > Done with solution" << std::endl;

    if (solution != nullptr) {
        std::cout << "Goal!!!" << std::endl;
        solution->draw(std::cout);
        std::cout << "\n";

        std::cout << "[8] curr size of balanced_list: " << send_back.size() << std::endl;

        this->printPath(std::cout, solution, 0);

        std::cout << "[9] curr size of balanced_list: " << send_back.size() << std::endl;

        send_back = this->balance_list;

        std::cout << "[10] curr size of balanced_list: " << send_back.size() << std::endl;

        this->drawBalanceList(std::cout);

        std::cout << "[11] curr size of balanced_list: " << send_back.size() << std::endl;
    }
    else {
        std::cout << "Failure!!!\n\n"
                  << "No answer was found. :(" << std::endl;
    }

    this->cleanInternalVariables(std::cout);
}

void ShippingPortDriver::drawBalanceList(std::ostream& out) const {
    out << "{";
    for (int i = 0; i < this->balance_list.size(); i++) {
        out << "(" << this->balance_list.at(i).first << ", "
            << this->balance_list.at(i).second << "), ";
    }
    out << "}" << std::endl;
    return;
}

<<<<<<< HEAD
void ShippingPortDriver::balance_ship_impossible() {
    // curr state -> sorted state
    // mass.at(0) = (1,6) // 1st heaviest
    // mass.at(1) = (1,7) // 2nd heaviest
    // mass.at(2) = (1,5) // 3rd heaviest
    // mass.at(3) = (1,8) // 4th heaviest


    std::vector<std::pair<int,int>> endCoords = this->ship->getCoords();
    std::vector<std::string> endNames = this->ship->getNames();
    std::vector<std::string> endMass = this->ship->getMasses();
    std::vector<int> sortMasses;
    for (int i = 0; i < ship->getMasses().size(); i++) {
//        std::cout << ship->getCoords().at(i).first << ", " << ship->getCoords().at(i).second << ": ";
//        std::cout << ship->getNames().at(i) << " - " << ship->getMasses().at(i) << std::endl;
        if (std::stoi(this->ship->getMasses().at(i)) != 0) {
            sortMasses.push_back(std::stoi(this->ship->getMasses().at(i)));
        }

    }



    std::sort(sortMasses.begin(), sortMasses.end()); // sort masses ascending order/descending order when looking back

    int right_ind = 7;
    int left_ind = 6;
    int right_lvl = 1;
    int left_lvl = 1;
    for (int k = 0; k < this->ship->getCoords().size(); k++) {

        if (std::stoi(this->ship->getMasses().at(k)) != 0) { // iterate through sortMasses for every Coord that is not NAN/Unused
            std::cout << "Mass is not 0: " << std::stoi(this->ship->getMasses().at(k)) << std::endl;


            for (int j = 0; j < sortMasses.size(); j++) {
                if (sortMasses.at(j) == 0) {break;} // can't move NAN stuff

                if (std::stoi(this->ship->getMasses().at(k)) == sortMasses.at(j)) {     // when CurrMass.at(k) = SortMass.at(j)
                    // asssuming no NAN
                    std::cout << "match: " << sortMasses.at(j) << std::endl;
                    if (j % 2 == 0) {
                        int temp_ind;
                        for (int i = 0; i < endCoords.size(); i++) { // find the coordinate where the sortMass matches actual mass
                            if (endCoords.at(i).first == right_lvl && endCoords.at(i).second == right_ind) {

                                temp_ind = i;
                                std::cout << "temp ind for R " << right_lvl << ", " << right_ind << " is " << temp_ind << std::endl;
                                std::cout << endNames.at(i) << " " << endCoords.at(i).first << ", " << endCoords.at(i).second << std::endl;
                                if (ship->getNames().at(temp_ind) == "NAN") {
                                    std::cout << "Jokes on ya, you can't move this block" << std::endl;

                                    while (ship->getNames().at(temp_ind) == "NAN") { // update right_ind and right_lvl until no longer "NAN"
                                        if (right_ind == 12 && right_lvl != 8) {
                                            right_ind = 7;
                                            right_lvl++;
                                            temp_ind += 6;
                                        }
                                        else {
                                            right_ind++;
                                            temp_ind++;
                                        }

                                    }

                                }
                                break;

                            }
                        }

                        //endCoords.at(temp_ind).first == right_lvl
                        //endCoords.at(temp_ind).second == right_ind
                        // sortMass.at(j) = ship->Mass.at(k)
                        // update ship->Names.at(k) = ship->Names.at(temp_ind)
                        // 1,2 - cat 1,6 - rat
                        // swap(cat, rat)
                        // 1,3 - dog 1,7 - unused

//                        std::string temp_name = endNames.at(temp_ind);
//                        endNames.at(temp_ind) = endNames.at(k);
//                        endNames.at(k) = temp_name;
//                        std::string temp_mass = endMass.at(temp_ind);
//                        endMass.at(temp_ind)= endMass.at(k);
//                        endMass.at(k) = temp_mass;
                          endNames.at(k) = ship->getNames().at(temp_ind);
                          endMass.at(k)= ship->getMasses().at(temp_ind);

//                        int temp_y = endCoords.at(temp_ind).first;
//                        int temp_x = endCoords.at(temp_ind).second;
//                        endCoords.at(temp_ind).first = endCoords.at(k).first;
//                        endCoords.at(temp_ind).second = endCoords.at(k).second;
//                        endCoords.at(k).first = temp_y;
//                        endCoords.at(k).second = temp_x;
                        sortMasses.at(j) = sortMasses.at(sortMasses.size()-1);
                        sortMasses.pop_back();
                        sort(sortMasses.begin(), sortMasses.end());

                        if (right_ind == 12 && right_lvl != 8) {
                            right_ind = 7;
                            right_lvl++;
                        }
                        else {
                            right_ind++;
                        }

                    }
                    } else {
                        int temp_ind;
                        for (int i = 0; i < endCoords.size(); i++) { // find the coordinate where the sortMass matches actual mass
                            if (endCoords.at(i).first == left_lvl && endCoords.at(i).second == left_ind) {
                                temp_ind = i;
                                std::cout << "temp ind for L " << left_lvl << ", " << left_ind << " is " << temp_ind << std::endl;

                                std::cout << endNames.at(i) << " " << endCoords.at(i).first << ", " << endCoords.at(i).second << std::endl;
                                if (endNames.at(i) != "NAN") {
                                    std::cout << "BOO" << std::endl;
                                    break;
                                }
                                else if (endNames.at(i) == "NAN") {
                                    std::cout << "Jokes on ya, you can't move this block" << std::endl;
                                    while (ship->getNames().at(temp_ind) == "NAN") { // update right_ind and right_lvl until no longer "NAN"
                                        if (left_ind == 0 && right_lvl != 1) {
                                            left_ind = 6;
                                            left_lvl++;
                                            temp_ind += 6;
                                        }
                                        else {
                                            left_ind--;
                                            temp_ind++;
                                        }

                                    }

                                }

                            }

                        }

                        //endCoords.at(temp_ind).first == right_lvl
                        //endCoords.at(temp_ind).second == right_ind


//                        endNames.at(temp_ind) = ship->getNames().at(k);
//                        endMass.at(temp_ind)= ship->getMasses().at(k);
                        endNames.at(k) = ship->getNames().at(temp_ind);
                        endMass.at(k)= ship->getMasses().at(temp_ind);

//                        int temp_y = endCoords.at(temp_ind).first;
//                        int temp_x = endCoords.at(temp_ind).second;
//                        endCoords.at(temp_ind).first = endCoords.at(k).first;
//                        endCoords.at(temp_ind).second = endCoords.at(k).second;
//                        endCoords.at(k).first = temp_y;
//                        endCoords.at(k).second = temp_x;

                        sortMasses.at(j) = sortMasses.at(sortMasses.size()-1);
                        sortMasses.pop_back();
                        sort(sortMasses.begin(), sortMasses.end());
                        std::cout << "mass size " << sortMasses.size() << std::endl;
                        if (left_ind == 0 && right_lvl != 1) {
                            left_ind = 6;
                            left_lvl++;
                        }
                        else {
                            left_ind--;
                        }


                    }
            }
        }


    }
    std::cout << "****************************************************************" << std::endl;

//    for (int i = 0; i < ship->getMasses().size(); i++) {
//        std::cout << ship->getCoords().at(i).first << ", " << ship->getCoords().at(i).second << ": ";
//        std::cout << ship->getNames().at(i) << " - " << ship->getMasses().at(i) << std::endl;

//    }





    for (int i = 0; i < ship->getCoords().size(); i++) {
        if (ship->getMasses().at(i) != "NAN" && ship->getNames().at(i) != "UNUSED" && ship->getNames().at(i) !="NAN") {
            std::cout << "Coor: " << ship->getCoords().at(i).first << ", " << ship->getCoords().at(i).second << " ";
            //std::cout << "Coor: " << endCoords.at(i).first << ", " << endCoords.at(i).second << " ";
            std::cout << "Name: " << ship->getNames().at(i) << " ";
            std::cout << "Mass: " << ship->getMasses().at(i) << std::endl;
        }
    }
    std::cout << std::endl;
    this->ship->setMass(endMass);
    this->ship->setNames(endNames);

    for (int i = 0; i < ship->getCoords().size(); i++) {
        if (ship->getMasses().at(i) != "NAN" && ship->getNames().at(i) != "UNUSED" && ship->getNames().at(i) !="NAN") {
            std::cout << "Coor: " << ship->getCoords().at(i).first << ", " << ship->getCoords().at(i).second << " ";
            //std::cout << "Coor: " << endCoords.at(i).first << ", " << endCoords.at(i).second << " ";
            std::cout << "Name: " << ship->getNames().at(i) << " ";
            std::cout << "Mass: " << ship->getMasses().at(i) << std::endl;
        }
    }

    this->ship->print_ship();

    // 0 = 6
    // 1 = 7
    // 2 = 5
    // 3 = 8
    // 4 = 4

    // 0 = 6   = 6 -0     1 = 7   = 7 + 0
    // 2 = 5   = 6 -1     3 = 8   = 7 + 1
    // 4 = 4   = 6 -2     5 = 9   = 7 + 2
    // 6 = 3   = 6 -3     7 = 10  = 7 + 3
    // 8 = 2   = 6 -4     9 = 11  = 7 + 4
    // 10 = 1  = 6 -5     11 = 12 = 7 + 5
    // 12 = 6  = 6 -0     13 = 7
    // j % 2 == 0: 6-(j/2)
    // (j % 12) % 2 == 0: y=j/12 + 1, x=6-((j%12)/2)
    // (j % 12) % 2 == 1: y=j/12 + 1, x=6+std::floor((j%12)/2)

//    if ((j%12) %2 == 0) {
//        std::cout  << "Mass needs to be at: " << j/12 + 1 << " " << 6- ((j%12)/2) << std::endl;
//        int temp_y = endCoords.at(k).first;
//        int temp_x = endCoords.at(k).second;


//        int temp_ind = 0;
//        for (int i =0; i < ship->getMasses().size(); i++) {
//            if (ship->getCoords().at(i).first == j/12 + 1 && ship->getCoords().at(i).second ==  6- ((j%12)/2)) {
//                temp_ind = i;
//                break;
//            }
//        }
//        std::cout  << "Mass coords currently" << ship->getCoords().at(temp_ind).first << " ";
//        std::cout << ship->getCoords().at(temp_ind).second << std::endl;

//        endCoords.at(k).first = j/12 + 1;
//        endCoords.at(k).second = 6- ((j%12)/2);
//        endCoords.at(temp_ind).first = temp_y;
//        endCoords.at(temp_ind).second = temp_x;


//        std::string temp_name = endNames.at(k);
//        endNames.at(k) = endNames.at(temp_ind);
//        endNames.at(temp_ind) = endNames.at(k);
////                        sortMasses.at(j) = sortMasses.at(sortMasses.size()-1);
////                        sortMasses.pop_back();
//        break;

//    } else {

//        std::cout  << "Mass needs to be at: " << j/12 + 1 << " " << 7+ ((j%12)/2) << std::endl;

//        int temp_y = endCoords.at(k).first;
//        int temp_x = endCoords.at(k).second;


//        int temp_ind = 0;
//        for (int i =0; i < ship->getMasses().size(); i++) {
//            if (ship->getCoords().at(i).first == j/12 + 1 && ship->getCoords().at(i).second == 7 +std::floor((j%12)/2)) {
//                temp_ind = i;
//                break;
//            }
//        }

//        std::cout  << "Mass coords currently" << ship->getCoords().at(temp_ind).first << " ";
//        std::cout << ship->getCoords().at(temp_ind).second << std::endl;

//        endCoords.at(k).first = j/12 + 1;
//        endCoords.at(k).second = 7+ std::floor((j%12)/2);
//        endCoords.at(temp_ind).first = temp_y;
//        endCoords.at(temp_ind).second = temp_x;


//        std::string temp_name = endNames.at(k);
//        endNames.at(k) = endNames.at(temp_ind);
//        endNames.at(temp_ind) = endNames.at(k);
////                        sortMasses.at(j) = sortMasses.at(sortMasses.size()-1);
////                        sortMasses.pop_back();
//        break;


//    }

=======
/*
std::priority_queue<ShipState*, std::vector<ShipState*>, Comp> frontier;
std::set<ShipState*> frontier_set;
std::set<ShipState*> explored;
int count;
int maxFrontierLength;
Ship* ship;
std::vector<std::pair<int, int>> balance_list;
*/
void ShippingPortDriver::cleanInternalVariables(std::ostream& out) {
    out << "cleaning internal variables" << std::endl;

    out << " - cleaning frontier set" << std::endl;
    this->frontier_set.clear(); // rid of frontier set, will be needed for multiple operations in one execution

    out << " - cleaning explored set" << std::endl;
    this->explored.clear(); // rid of the explored set, will be needed for multiple operations in one execution

    // get rid of priority queue
    out << " - cleaning frontier" << std::endl;
    while(!this->frontier.empty()) {
        this->frontier.pop();
    }

    out << " - cleaning balance_list" << std::endl;
    // clear balance list
    this->balance_list.clear();

    if (this->startState) {
        out << " - cleaning ShipState tree" << std::endl;
        this->clearShipStateTree(this->startState, out);
    }

}

void ShippingPortDriver::clearShipStateTree(ShipState* curr, std::ostream& out) {
   if (curr->getChildrenLength() == 0) {
       out << "     - reached child" << std::endl;
       delete curr;
       return;
   } // when we get to a leaf just return

    // go thru every child when they exist, and recursive call
    // given the child, imagine a new tree root at that node
    for (int i = 0; i < curr->getChildrenLength(); i++) {
        this->clearShipStateTree(curr->getChild(i), out);
    }
    // delete current, probably a leaf
    delete curr;
>>>>>>> f3f6173c25e92df0fea939e3f6629b539af6eed6
}
