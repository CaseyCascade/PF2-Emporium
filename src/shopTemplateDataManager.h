#pragma once

#include <iostream>
#include <filesystem> 
#include <fstream>

#include "shopTemplate.h"

using namespace std; 
namespace fs = filesystem; 

class ShopTemplateDataManager {
    protected:
        fs::path coreTemplateDirectory = fs::current_path().parent_path() / "data" / "core_templates";
        fs::path customTemplateDirectory = fs::current_path().parent_path() / "data" / "custom_templates";

    public: 
        ShopTemplateDataManager();
        string getVariable(string line);
        vector <ShopTemplate> loadFile(string filepath);
        vector <ShopTemplate> load();  
        void saveCustomTemplate(string filename, vector <ShopTemplate>);
}; 