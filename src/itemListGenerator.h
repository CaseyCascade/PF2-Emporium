#pragma once

#include <iostream> 
#include <random>

#include "scoredTable.h"

using namespace std; 

class ItemListGenerator {
    protected:
        vector <pair <Item, int>> scoredTable; 
        float percentile; 
        int target; 

        vector <int> pickedItemIndexes; 
        bool debug = true; 
    public:
        // Constructor
        ItemListGenerator(vector <pair <Item, int>> t, float p); 

        // Getters
        vector <int> getScoreRange(); 
        int getAverage(vector <int> pickedNumbers); 

        // Member Functions
        bool searchVector(vector <int> range, int n); 
        void rubberbandRecursion(vector <int> &pickedNumbers, int N); 
        void rubberbandGenerator(int N); 


        // Print
        void printVector(vector <int> range);
        void printResults(); 

}; 