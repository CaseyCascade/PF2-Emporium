#pragma once
 
#include <iostream>
#include <vector> 

using namespace std; 

class Item {
    protected:
        string name; 
        int page; 
        float gold; 
        int level; 
        float bulk; 
        string source;
        string entry; 
        vector <string> traits;

    public: 
        Item();
        // Setters
        void setName (string x);
        void setPage (int x);
        void setGold (float x);
        void setLevel (int x);
        void setBulk (float x);
        void setSource (string x);
        void setEntry (string x);
        void addTrait (string x);
        void enterData (string variable, string data); 

        // Getters
        string getName ();
        int getPage ();
        float getGold ();
        int getLevel ();
        float getBulk ();
        string getSource ();
        string getEntry ();
        vector <string> getTraits ();

        // Other
        void clear (); 
}; 