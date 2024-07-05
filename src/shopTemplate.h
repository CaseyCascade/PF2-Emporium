#pragma once 

#include <iostream>
#include <vector>

#include "item.h"

using namespace std; 

class ShopTemplate {
    protected:
        vector <pair <string, int> > weightedTraits; 
        vector <string> sourceBlacklist;
        vector <string> traitBlacklist; 
        int levelMin = -69; 
        int levelMax = -69; 

    public:
        // Constructors
        ShopTemplate();
        ShopTemplate(vector <string> traits); 
        ShopTemplate(vector <string> traits, int min, int max); 
        ShopTemplate(vector <ShopTemplate> templates); // For Combining Multiple Templates into One  

        // Setters
        void setWeights(vector <string> traits); 
        void setLevelRange(int min, int max);

        // Getters 
        vector <pair<string, int>> getWeightedTraits(); 
        vector <string> getSourceBlacklist(); 
        vector <string> getTraitBlacklist();

        // Member Functions
        bool acceptLevel (int level); 
        ShopTemplate combine (ShopTemplate templateOne, ShopTemplate templateTwo);

        // Print
        void print(); 

}; 