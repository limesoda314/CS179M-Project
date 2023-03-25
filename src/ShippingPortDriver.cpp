#include "../headers/ShippingPortDriver.h"
#include "../headers/Ship.h"

ShippingPortDriver::ShippingPortDriver() {
    this->count = 0;
}

/* Can run AStar and Uniform Cost Search */
ShipState* ShippingPortDriver::graphSearch(ShipState* problem) {

    // Initialize the frontier using the initial state of problem
    this->frontier.push(problem);
    this->frontier_set.insert(problem);

    // Tracking max frontier length
    if (this->frontier.size() > this->maxFrontierLength) {
        this->maxFrontierLength = this->frontier.size();
    }

    // loop do
    while (true) {
        // If frontier is empty, then return failure
        if (this->frontier.size() == 0) { return nullptr; }

        // Pick the smallest leaf, based on algorithm
        ShipState* leaf = this->frontier.top();

        this->frontier.pop();
        this->frontier_set.erase(leaf);

        // If leaf is the goal, return it
        if (*(this->goal) == *leaf) { 
            return leaf;
        } // Overloaded== // TODO - CHECK

        // Add to explored set if not
        this->explored.insert(leaf);

        // // If not in explored, expand
        // std::cout << "==============================================================\nCurrent expanding node with g(n) = "
        //           << leaf->getCost() << ", h(n) = " << leaf->heuristic() << ", and f(n) = " << leaf->f_valueFrom() << "\n";
        
        leaf->draw(std::cout);
        leaf->expandNode();

        this->count++;

        // std::cout << "Expanding node " << this->count << "...\n";
        // std::cout << "Size: " << this->frontier_set.size() << "\n\n";

        // Add the children to the frontier if not there or in explored
        for (int i = 0; i < 4; i++) {

            // Child is not in frontier
            bool in_frontier = ( this->frontier_set.find(leaf->getChild(i)) != this->frontier_set.end() );

            // Child is not in explored
            bool in_explored = ( this->explored.find(leaf->getChild(i)) != this->explored.end() );

            // If both conditions are met, push into frontier
            if ( !in_frontier && !in_explored ) {
                this->frontier.push( leaf->getChild(i) );
                this->frontier_set.insert( leaf->getChild(i) );

                // Tracking maximum frontier length
                if (this->frontier.size() > this->maxFrontierLength) {
                    this->maxFrontierLength = this->frontier.size();
                }
            }

        }
    } 
}

void ShippingPortDriver::menu() {
    char option;

    this->root = new Ship();

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
            Ship1->load_manifest(testpath);
            
        }
        else if (option == '2') {
            if (Ship1->get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl; 
            }
            else {
                Ship1->read_manifest();
            }
            
        }
        else if (option == '3') {
            if (Ship1->get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl; 
            }
            else {
                Ship1->create_outbound();
            }
        }
        else if (option == '4') {
            time_t now = time(0); 
            tm *ltm = localtime(&now);

            std::cout << "Will log to logfile_" << std::to_string(1900 + ltm->tm_year) << ".txt" << std::endl; 
            std::cout << "Single line comment: " << std::endl; 
            std::string comment;
            std::cin.ignore();
            std::getline(std::cin, comment);

            Ship1->log_comment(comment); 
        }
        else if (option == '5') {
            Ship1->view_logfile(); 
        }
        else if (option == '6') {
            if (Ship1->get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl; 
            } else {
                Ship1->print_ship();
            }
        }
        else if (option == '7') {
            if (Ship1->get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl; 
            } else {
                Ship1->balance_score();
            }
        }
        else if (option == '8') {
            if (Ship1->get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl; 
            } else {
                Ship1->balance_ship();
            }
        }
        else if (option == '9') {
            if (Ship1->get_manifest_name() == "") {
                std::cout << "Load a manifest first" << std::endl;
            } else {
                Ship1->load_unload_ship();
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
    if (leaf == nullptr) { return; }
    printPath(out, leaf->getParent(), i - 1);
    out << i << ")\n";
    leaf->draw(std::cout);
}

void ShippingPortDriver::defaultTest() {

    ShipState* board = new ShipState(
        this->Ship
    );

    std::cout << "Setting heuristic to " << heur << ".\n";
    problem->setHeuristic(heur);
    board->setContext(problem);

    // Graph search algorithm
    Board* solution = this->graphSearch(problem);
    if (solution != nullptr) {
        std::cout << "Goal!!!" << std::endl;
        solution->draw(std::cout);
        std::cout << "\n"
                  << "To solve this problem the search algorithm expanded a total of " << this->count << " nodes.\n"
                  << "The maximum number of nodes in the queue at any one time: " << this->maxFrontierLength << "\n"
                  << "The depth of the goal node was: " << solution->getDepth() << std::endl;

        std::cout << "\n";
        this->printPath(std::cout, solution, solution->getDepth());
    }
    else {
        std::cout << "Failure!!!\n\n"
                  << "No answer was found. :(" << std::endl;
    }

}