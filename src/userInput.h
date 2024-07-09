#pragma once 

// Standard Libraries
#include <iostream> 
#include <sstream> 
#include <cstdlib> 

// Internal Includes
#include "commandPalette.h"

class UserInput {
    protected:
    CommandPalette command; 
    string input; 

    public:
    // Utility
    void clearScreen(); 
    void printBanner(); 
    int convertToInt(const string& str);
    

    // Generate from Shops
    void listGeneration();  
    void viewShop(int userShopindex); 
    void displayItemList(vector <Item> items, int userShopIndex);
    void displayItem(vector<Item> currentList, int userShopIndex, Item itemToDisplay, bool noList);

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