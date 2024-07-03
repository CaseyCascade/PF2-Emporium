#pragma once

#include <iostream>
#include <filesystem> 
#include <fstream>

#include "item.h"

using namespace std; 
namespace fs = filesystem; 

class ItemDataManager {
    protected:
        fs::path coreItemDirectory = fs::current_path().parent_path() / "data" / "core_items";
        fs::path customItemDirectory = fs::current_path().parent_path() / "data" / "custom_items";

    public: 
        ItemDataManager();
        string getVariable(string line);
        vector <Item> loadFile(string filepath); 
        vector <Item> load();
        void saveCustomItems(vector <Item>, string filename);
        
}; 