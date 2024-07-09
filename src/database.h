#pragma once

// Standard Libraries
#include <iostream> 
#include <vector> 
#include <string>
#include <algorithm>
#include <cctype>

// Internal Includes
#include "item.h"
#include "itemDataManager.h"
#include "shopTemplate.h" // TODO Need to implement shopPatterns into the Database
#include "shopTemplateDataManager.h"

class Database {
    protected:
        vector <Item> itemDatabase; 
        vector <string> traitDatabase; 
        vector <ShopTemplate> templateDatabase; 
        
    public:
        // Constructor
        Database();

        //Setters
        string trim(const std::string& str);
        void setTraitDatabase();
        void loadItems();
        void loadTemplates();
        void load(); 

        // Getters
        vector <Item> getItemDatabase();
        vector <string> getTraitDatabase(); 
        vector <ShopTemplate> getTemplateDatabase(); 
        Item getItem (string name); 
        ShopTemplate getShop (string shop); 

        // Member Functions
        bool searchTraitDatabase(string s);
        void printTraits();
        void printItems(); 
        void printTemplates();
        bool searchVector(vector <string> vec, string s);
        void fixTraits();  
};