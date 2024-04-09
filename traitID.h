#include <iostream> 
#include <string>
#include <vector> 
#include <tuple> 
#include <algorithm>
#include <cctype>
#include <locale>

using namespace std; 

// trim from start (in place)
inline void ltrim(std::string &s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](unsigned char ch) {
        return !std::isspace(ch);
    }));
}

// trim from end (in place)
inline void rtrim(std::string &s) {
    s.erase(std::find_if(s.rbegin(), s.rend(), [](unsigned char ch) {
        return !std::isspace(ch);
    }).base(), s.end());
}

void trim(string &input)
{
    ltrim(input);
    rtrim(input);
}

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
        trim(head);
        return head; 
    }

    // INSERT //

    void insert(string s)
    {
        string trait = parse_trait(s);
        if (!search(trait))
        {
            if (trait.size() < 15) //Excludes ridiculously long Region/Organization based and Ammunition traits
            {
                traitTable.push_back(trait); 
            } 
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