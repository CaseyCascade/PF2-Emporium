#pragma once

// Standard Libraries
#include <iostream> 
#include <vector> 
#include <string>

// Internal Includes
#include "item.h"
#include "itemDataManager.h"
#include "shopTemplate.h" // TODO Need to implement shopPatterns into the Database
#include "shopTemplateDataManager.h"

class Database {
    protected:
        vector <Item> itemDatabase; 
        vector <string> traitDatabase; 
        vector<filesystem::path> itemDirectories = { // TODO Move this functionality into ItemDataManager.cpp 
            filesystem::current_path().parent_path() / "data" / "core_items",
            filesystem::current_path().parent_path() / "data" / "custom_items"
        };
    public:
        Database();
        bool searchTraitDatabase(string s);
        void setTraitDatabase();
        void loadItems();
        void load(); 
        void printTraits();
        void print(); 
};