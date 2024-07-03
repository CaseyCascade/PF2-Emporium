#pragma once 

#include <iostream>
#include <vector>
#include <filesystem> 

#include "item.h"

using namespace std; 

class ShopTemplate {
    protected:
        vector <pair <string, int> > weightedTraits; 
        vector <string> sourceBlacklist;
        vector <string> traitBlacklist; 
        int levelMin = -1; 
        int levelMax = -1; 

    public:
        ShopTemplate();
        ShopTemplate(vector <string> traits, int min, int max); 
        ShopTemplate(vector <ShopTemplate> templates); 


}; 