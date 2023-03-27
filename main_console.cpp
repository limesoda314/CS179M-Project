#include <iostream> 
#include "headers/Ship.h" 
#include "headers/ShippingPortDriver.h"

int main(int argc, char** argv) {

    std::cout << "Beginning application." << std::endl;

    ShippingPortDriver* newDriver = new ShippingPortDriver();

    newDriver->menu();

    return 0;
}