#pragma once

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm> 
#include <cctype> 
#include <queue>
#include <iomanip> 

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
        float version = 0.1; 
        string input; 

    public:
        // Constructors
        CommandPalette(); 

        // Utility
        int convertToInt (const string& str); 
        bool isAllUppercase(const string& str);
        bool isAllLowercase(const string& str); 
        queue <string> splitString(const string& str);
        string border(); 
        void printColumns(const vector<string>& data, int numColumns);
        vector<string> concatenate(const vector<string>& v1, const vector<string>& v2);

        // Getters
        vector <ShopTemplate> getTemplateDatabase(); 

        // Member Functions
        vector <Item> generateItemsFromShop(string shop, int numItems); 
        Item itemLookup (string itemName); 

        // Print
        void clearScreen(); 
        void displayBanner(); 
        void invalidInput();
        
        // Commands
        void listShops();
        void listTraits();
        void listItems(queue <string> args); 
        void listFork(queue <string> args); 

        void generate(queue <string> args);

        void lookupShop(queue <string> args);
        void lookupItem(queue <string> args);
        void lookupFork(queue <string> args); 

        void createShop();
        void createItem(); 
        void createFork(queue <string> args);

        void combine(queue <string> args);
        void reset();  
        void nuke(); 
        void help(); 

        // Input Parsing 
        void runCommand (string command, queue <string> args);
        void processLine (queue <string> commands);  
        void run(); 
        void startup(); 
}; 