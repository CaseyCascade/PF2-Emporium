#pragma once

#include <iostream>

#include "database.h"
#include "shopTemplate.h"
#include "scoredTable.h"
#include "itemListGenerator.h"

class CommandPalette {
    protected:
        Database database; 
    public:
        // Constructors
        CommandPalette(); 

        // Getters
        vector <ShopTemplate> getTemplateDatabase(); 

        // Member Functions

        // Print
        void viewShop(int index); 
        void displayShopList();
        void displayTraits(); 


}; 