#include <iostream> 
#include "headers/Ship.h" 
#include "headers/ShippingPortDriver.h"

int main(int argc, char** argv) {

    std::cout << "Beginning application." << std::endl;

    ShippingPortDriver* newDriver = new ShippingPortDriver();

    int ret = newDriver->QTGUI(argc, argv);

    return ret;
}
