#pragma once 

#include <iostream>
#include <sstream>
#include <vector>

#include "item.h"

using namespace std; 

#define EMPTY -69
#define MIN_LEVEL -1
#define MAX_LEVEL 30

class ShopTemplate {
    protected:
        string templateName; 
        vector <pair <string, int> > weightedTraits; 
        vector <string> sourceBlacklist;
        vector <string> traitBlacklist; 
        int levelMin = EMPTY; 
        int levelMax = EMPTY; 

    public:
        // Constructors
        ShopTemplate();
        ShopTemplate(string errorMessage); 
        ShopTemplate(string name, vector <string> traits); 
        ShopTemplate(string name, vector <string> traits, int min, int max); 
        ShopTemplate(string name, vector <string> traits, int min, int max, vector <string> blacklistSources, vector <string> blacklistTraits);
        ShopTemplate(string name, vector <ShopTemplate> templates); // For Combining Multiple Templates into One  

        // Setters
        void setName(string name); 
        void addWeightedTrait (string trait, int weight); 
        void addBlacklistedSource(string source); 
        void addBlacklistedTrait(string trait); 
        void setLevelMin(int min); 
        void setLevelMax(int max); 
        void setDefaultWeights(vector <string> traits); 
        void setLevelRange(int min, int max);
        void clear(); 
        bool enterData(string variable, string data); 

        // Getters 
        string getName(); 
        vector <pair<string, int>> getWeightedTraits(); 
        vector <string> getSourceBlacklist(); 
        vector <string> getTraitBlacklist();
        int getLevelMin();
        int getLevelMax(); 
        bool isDefaultLevelRange();
        bool isBlacklisted(string s); 
        int searchTrait(string trait); 

        // Member Functions
        bool acceptLevel (int level); 
        void deleteTrait(string Trait);
        void removeBlacklistedTraits();
        void combine (ShopTemplate &templateTwo);

        // Print
        void print(); 

}; 