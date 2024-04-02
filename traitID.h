#include <iostream> 
#include <string>
#include <vector> 
#include <tuple> 

using namespace std; 

class traitID {
    vector <string> traitTable; 

    public: 
    traitID() {}

    // SEARCH
    bool search (string s) 
    {
        for (auto i : traitTable)
        {
            if (i == s) return true; 
        }
        return false; 
    }

    // Input Parsing //
    string parse_trait(string input)
    {
        string head; 
        bool found = false; 
        for (auto i : input)
        {
            if (i == '<' || i == '(' || i == '|')
            {
                break; 
            }
            head.push_back(i);
        }
        return head; 
    }

    // INSERT //

    void insert(string s)
    {
        if (!search(s))
        {
            traitTable.push_back(parse_trait(s));  
        }
        return;
    }

    void remove(string s)
    {
        vector <string> newTable; 
        for (int i = 0; i < traitTable.size(); i++)
        {
            if (traitTable.at(i) != s)
            {
                newTable.push_back(s);
            }
        }
        traitTable = newTable; 
    }

    void clear()
    {
        traitTable.clear(); 
    }

    // LOAD / SAVE //
    void load () {}
    void save () {}
    void update() {}
    void check_for_update() {}

    // DEBUG //
    void print()
    {
        cout << "--- Traits ---" << endl; 
        for (int i = 0; i < traitTable.size(); i++){
            cout << i << ": " << traitTable.at(i) << endl; 
        }
        cout << endl; 
    }

};