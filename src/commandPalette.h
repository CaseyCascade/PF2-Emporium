#pragma once

#include <iostream>

#include "database.h"
#include "shopTemplate.h"
#include "scoredTable.h"
#include "itemListGenerator.h"

class CommandPalette {
    protected:
        Database database; 
        Database *ptr = &database;

    public:
        // Constructors
        CommandPalette(); 

        // Getters
        vector <ShopTemplate> getTemplateDatabase(); 

        // Member Functions
        vector <Item> generateItemsFromShop(int shopIndex, int numItems); 
        Item itemLookup (string itemName); 

        // Print
        void viewShop(int index); 
        void displayShopList();
        void displayTraits(); 


}; 