#pragma once

// Standard Libraries
#include <iostream> 
#include <vector> 

// Internal Includes
#include "shopTemplate.h"
#include "database.h"
#include "item.h"

class ScoredTable {
    protected:
        Database* pointerDatabase; 
        ShopTemplate shopTemplate; 
        vector <pair <Item, int>> scoredTable; 
    public:
        // Constructors  
        ScoredTable(); 
        ScoredTable(Database* global, ShopTemplate shop);
        
        // Getters
        vector <pair <Item, int>> getScoredTable(); 

        // Member Functions
        void countingSort(); 
        bool earlyReject(Item current);
        int calculateScore(Item current); 
        void generate(); 
        // Print
        void print(); 


}; 