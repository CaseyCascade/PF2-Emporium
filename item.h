#include "traitID.h"

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
        trim(x);
        name = x; 
    }
    void addSource(string x)
    {
        for (auto &i : x)
        {
            if (i == '|') 
            {
                i = ' '; 
                trim(x);
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
        trim(entry);
    }
    void addTrait (string s) //TODO "modular" is being input twice when parsed
    {
        trim(s);        
        traits.insert(s);
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
        traits.clear();
        otherSources.clear(); 
    }
    void printSources()
    {
        if (!otherSources.empty()) {for (auto &i : otherSources) cout << "Other Sources: " << i << ", \n";} 
    }
    void printTraits() // TODO 
    {
        traits.print(); 
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