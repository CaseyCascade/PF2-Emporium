#include "traitDB.h"
#include <algorithm>

class Item {
    private: 
    string name; 
    string originSource;  
    string coin;
    string entry;
 
    int page; 
    int level;
    double bulk; 
    double price;

    vector <string> otherSources; 
    traitID traits; 

    public: 
    // CONSTRUCTORS //
    Item()
    {
        name = originSource = coin = entry = "NA"; 
        page = level = price = bulk = -1; 
        otherSources.clear();
        traits.clear(); 
    }

    // SETTERS // 
    void setName(string x)
    {
        name = x; 
    }
    void addSource(string x)
    {
        for (auto &i : x)
        {
            if (i == '|') 
            {
                i = ' '; 
                otherSources.push_back(x);
                return; 
            }
        }
        originSource = x; 
    }
    void setPage(int x)
    {
        page = x; 
    }
    void setLevel(int x)
    {
        level = x; 
    }
    void setPrice(int x)
    {
        price = x; 
    }
    void setCoin(string x)
    {
        coin = x; 
    }
    void setBulk (int x)
    {
        bulk = x; 
    }
    void addEntry(string x)
    {
        if (entry == "NA") entry.clear(); 
        entry += " " + x; 
    }
    void addTrait (string x)
    {

    }

    // GET //
    string getName() 
    {
        return name; 
    }
    // Functions // 
    void clear()
    {
        name = originSource = coin = entry = "NA"; 
        page = level = price = bulk = -1; 
    }
    void printSources()
    {
        if (!otherSources.empty()) {for (auto &i : otherSources) cout << "Other Sources: " << i << ", \n";} 
    }
    void printTraits() // TODO 
    {
        cout << "--- Traits ---" << endl; 
    }
    void print()
    {
        cout << "--- " << name << " ---" << endl; 
        cout << "Original Source: "; 
        cout << originSource << " " << page << endl; 
        printSources(); 
        cout << "Level: " << level << endl; 
        cout << "Price: " << price << " " << coin << endl; 
        cout << "Bulk: " << bulk << endl;
        cout << "Entry: " << entry << endl << endl; 
        printTraits();  
    }
};