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
    TraitID traits; 

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
    void set_name(string x)
    {
        trim(x);
        name = x; 
    }
    void add_source(string x)
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
    void set_page(int x)
    {
        page = x; 
    }
    void set_level(int x)
    {
        level = x; 
    }
    void set_price(int x)
    {
        price = x; 
    }
    void set_coin(string x)
    {
        coin = x; 
    }
    void set_bulk (int x)
    {
        bulk = x; 
    }
    void add_entry(string x)
    {
        if (entry == "NA") entry.clear(); 
        entry += " " + x; 
        trim(entry);
    }
    void add_trait (string s) 
    {
        trim(s);       
        traits.insert(s);
    }
    void finish_initialization() // Need to copy traits to a repository of all known traits. 
    {
        if (level == -1) level = 0; 
        traits.toUpperTable();
    }

    // GET //
    string get_name() 
    {
        return name; 
    }
    string get_origin_source()
    {
        return originSource; 
    }
    int get_level()
    {
        return level; 
    }
    bool search_trait(string trait)
    {
        return traits.search(trait); 
    }
    // Functions // 
    void clear()
    {
        name = originSource = coin = entry = "NA"; 
        page = level = price = bulk = -1; 
        traits.clear();
        otherSources.clear(); 
    }
    void print_sources()
    {
        if (!otherSources.empty()) {for (auto &i : otherSources) cout << "Other Sources: " << i << ", \n";} 
    }
    void print_traits() 
    {
        traits.print(); 
    }
    void print()
    {
        cout << "--- " << name << " ---" << endl; 
        cout << "Original Source: "; 
        cout << originSource << " " << page << endl; 
        print_sources(); 
        cout << "Level: " << level << endl; 
        cout << "Price: " << price << " " << coin << endl; 
        cout << "Bulk: " << bulk << endl;
        cout << "Entry: " << entry << endl << endl; 
        print_traits();  
    }
};