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
        vector <ShopTemplate> loadFile();
        vector <ShopTemplate> load();  
        void saveToFile(vector <ShopTemplate>, bool isCustomTemplate);
}; 