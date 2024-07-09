#pragma once

#include <iostream>
#include <cstdlib>
#include <algorithm> 
#include <cctype> 

#include "item.h"
#include "shopTemplate.h"
#include "database.h"
#include "itemDataManager.h"
#include "shopTemplateDataManager.h"
#include "scoredTable.h"
#include "itemListGenerator.h"

class CommandPalette {
    protected:
        Database database; 
        Database *ptr = &database;

    public:
        // Constructors
        CommandPalette(); 

        // Utility
        int convertToInt (const string& str); 
        bool isAllUppercase(const string& str);
        bool isAllLowercase(const string& str); 
        
        // Getters
        vector <ShopTemplate> getTemplateDatabase(); 

        // Member Functions
        vector <Item> generateItemsFromShop(int shopIndex, int numItems); 
        Item itemLookup (string itemName); 

        // Print
        void clearScreen(); 
        void displayBanner(); 
        void viewShop(int index); 
        void displayShopList();
        void displayTraits(); 

        // Commands
        void generate(string shop, int numItems);
        void lookup(string shopOrItem); // Shops are always in uppercase, items in lowercase
        void create(bool shop, string name);
        void combine(string shopOne, string shopTwo, string name);
        void reset();  
        void help(); 

        // Input Parsing 
        void runCommand (string command);
        void processLine (string line);  
        void run(); 

}; 