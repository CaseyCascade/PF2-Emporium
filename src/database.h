#pragma once

// Standard Libraries
#include <iostream> 
#include <vector> 
#include <string>
#include <fstream>

// Internal Includes
#include "item.h"

class Database {
    protected:
        vector <Item> itemDatabase; 
        vector <string> traitDatabase; 
        vector <string> itemDirectories = {}; //TODO
    public:
        Database();
        string getVariable(string);
        void loadFile(string filepath);
        void load();
};