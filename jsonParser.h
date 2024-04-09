//Internal Libraries
#include <fstream>
#include <cctype> 
#include <queue> 
#include <filesystem> 

using namespace std::filesystem;

//json 
#include "include/json.hpp"
using json = nlohmann::json;

//File dependencies
#include "item.h"

struct JsonParser {
    string temp; 

    JsonParser() {}

    bool ignore_var(string s)
    {
        vector <string> ignored_variables = 
        {
        "equipment", "remaster", 
        };

        for (auto &i : ignored_variables) if (i == s) return true;
        return false; 
    }

    void initialize (json item, Item &newItem)
    {
        for (auto &i : item.items()) //Individual Item 
        {
            if (ignore_var(i.key())) continue; 
            
            // Recursion // 
            if (i.value().is_object()) initialize (i.value(), newItem); // Recursive Call into SubObject
            
            // Hard Coded Data Entries //
            else if (i.key() == "name") newItem.set_name(i.value());
            else if (i.key() == "source") newItem.add_source(i.value()); 
            else if (i.key() == "otherSources") newItem.add_source(i.value());
            else if (i.key() == "page") newItem.set_page(i.value()); 
            else if (i.key() == "level") newItem.set_level(i.value());
            else if (i.key() == "amount") newItem.set_price(i.value()); 
            else if (i.key() == "coin") newItem.set_coin(i.value()); 
            else if (i.value().is_boolean()) newItem.add_trait(i.key()); 
                
            // Cases of Possible Differing Data Types //
            else if (i.key() == "entries")  //There are sometimes sub-objects here, but we're choosing to ignore them
            {
                for (auto &j : i.value()) if (j.is_string()) newItem.add_entry(j); 
            }
            else if (i.key() == "bulk")
            {
                if (i.value().is_string())
                {
                    if (i.value() == "L") newItem.set_bulk(0.1); 
                    else newItem.set_bulk(0); 
                }
                else newItem.set_bulk(i.value()); 
            }
            else if (i.key() == "hands")
            {
            if (i.value().is_string()) temp = i.value();
                else temp = to_string(i.value());
                temp += " hand(s)"; 
                newItem.add_trait(temp); 
                temp.clear(); 
            }

            // Trait Entries //
            else if (i.value().is_string()) newItem.add_trait(i.value()); 
            else if (i.value().is_array() && i.key() != "entries") //Array
            {
                for (auto &j : i.value())
                {
                    if (j.is_string()) 
                    {
                        if (i.key() == "Originally" || i.key() == "Reprinted") newItem.add_source(j);
                        else newItem.add_trait(j);
                    }
                    else 
                    {
                        cout << "ERROR: Found a non-string in an array\n"; 
                        cout << "KEY: " << i.key() << " VALUE: " << j << endl; 
                        exit(0); 
                    }
                }
            }
        }
    }

    vector <Item> read_from_json(path filePath)
    {
        vector <Item> storedItems;
        ifstream file (filePath);
        json input = json::parse(file);
        
        Item newItem;  
        int count = 0;

        for (auto &i : input) // Each Array is an Input File's set of Items 
        {
            for (auto &j : i.items()) // Contains Each Individual Item per Input File 
            { 
                initialize(j, newItem); // Called on Each Item, iterates through their Objects 
                storedItems.push_back(newItem); 
                newItem.clear();
            }
        }
        return storedItems; 
    }
};