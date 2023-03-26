#include "../headers/ShippingPortDriver.h"
#include "../headers/Ship.h"

ShippingPortDriver::ShippingPortDriver() {
    this->count = 0;
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
    if (this->frontier.size() > this->maxFrontierLength) {
        this->maxFrontierLength = this->frontier.size();
    }

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
        } // Overloaded== // TODO - CHECK

        // std::cout << "                  > adding to explored" << std::endl;
        // Add to explored set if not
        this->explored.insert(leaf);

        // If not in explored, expand
        // std::cout << "==============================================================\n Current expanding node with g(n) = "
                //   << leaf->getCost() << ", h(n) = " << leaf->heuristic() << ", and f(n) = " << leaf->f_valueFrom() << "\n";
        
        // std::cout << "                  > drawing current state" << std::endl;
        leaf->draw(std::cout);

        // std::cout << "                  > expanding state..." << std::endl;
        leaf->expandNode();

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

void ShippingPortDriver::menu() {
    char option;

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
                this->balance_ship();
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
    
    leaf->draw(std::cout);
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

void ShippingPortDriver::balance_ship() {

    std::cout << "Attempting to balance ship. Loading..." << std::endl;

    std::cout << " > Creating starting ship state" << std::endl; 
    ShipState* startState = new ShipState(
        this->ship->getCoords(),
        this->ship->getMasses(),
        this->ship->getNames(),
        new BalanceFactorHeuristic(),
        nullptr
    );

    std::cout << " > Creating solution (may take a while)..." << std::endl;
    // Graph search algorithm
    ShipState* solution = this->graphSearch(startState);

    std::cout << "   > Done with solution" << std::endl;

    if (solution != nullptr) {
        std::cout << "Goal!!!" << std::endl;
        solution->draw(std::cout);
        std::cout << "\n";
        this->printPath(std::cout, solution, 0);
        this->drawBalanceList(std::cout);
    }
    else {
        std::cout << "Failure!!!\n\n"
                  << "No answer was found. :(" << std::endl;
    }

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