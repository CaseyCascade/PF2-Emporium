#pragma once

// Standard Libraries
#include <iostream> 
#include <vector> 
#include <string>

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
        void setTraitDatabase();
        void loadItems();
        void loadTemplates();
        void load(); 

        // Getters
        vector <Item> getItemDatabase();
        vector <string> getTraitDatabase(); 
        vector <ShopTemplate> getTemplateDatabase(); 

        // Member Functions
        bool searchTraitDatabase(string s);
        void printTraits();
        void printItems(); 
};