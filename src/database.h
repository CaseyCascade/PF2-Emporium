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
        vector <filesystem::path> itemDirectories = {"data/core_items", "data/custom_items"}; //TODO
    public:
        Database();
        string getVariable(string);
        void loadFile(string filepath);
        void load();
        void print(); 
};