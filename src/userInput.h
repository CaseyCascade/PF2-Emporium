#pragma once 

// Standard Libraries
#include <iostream> 
#include <sstream> 
#include <cstdlib> 

// Internal Includes
#include "commandPalette.h"

class UserInput {
    protected:

    public:
    // Utility
    void clearScreen(); 
    void printBanner(); 

    // Generate from Shops
    void listGeneration();  
    // Generate Shops (?)
    
    // Create Shops
    void shopCreation();
    // Create Items
    void itemCreation();
    // Search Item
    void itemSearch(); 
    // Run
    void startMenu(); 
}; 