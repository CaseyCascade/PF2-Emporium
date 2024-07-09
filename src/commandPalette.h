#pragma once

#include <iostream>
#include <sstream>
#include <cstdlib>
#include <algorithm> 
#include <cctype> 
#include <queue>

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
        vector <string> validCommands = 
        {
        "help", "list shops", "list traits", "list items", "generate", 
        "lookup shop", "lookup item", "create shop", "create item", "combine", "reset", "nuke custom", "clear"
        };

    public:
        // Constructors
        CommandPalette(); 

        // Utility
        int convertToInt (const string& str); 
        bool isAllUppercase(const string& str);
        bool isAllLowercase(const string& str); 
        queue <string> splitString(const string& str);
        bool isValidCommand (string str); 
        string border(); 

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
        void lookupShop(string str);
        void lookupItem(string str);
        void create(bool shop, string name);
        void combine(string shopOne, string shopTwo, string name);
        void reset();  
        void help(); 

        // Input Parsing 
        void runCommand (string command, queue <string> args);
        void processLine (queue <string> commands);  
        void run(); 
        void startup(); 
}; 