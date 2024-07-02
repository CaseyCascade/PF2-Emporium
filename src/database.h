#pragma once

// Standard Libraries
#include <iostream> 
#include <vector> 
#include <string>
#include <fstream>
#include <filesystem>

// Internal Includes
#include "item.h"

class Database {
    protected:
        vector <Item> itemDatabase; 
        vector <string> traitDatabase; 
        vector<filesystem::path> itemDirectories = {
            filesystem::current_path().parent_path() / "data" / "core_items",
            filesystem::current_path().parent_path() / "data" / "custom_items"
        };
    public:
        Database();
        string getVariable(string);
        bool searchTraitDatabase(string s);
        void setTraitDatabase();
        void loadFile(string filepath);
        void load();
        void printTraits();
        void print(); 
};