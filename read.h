//Internal Libraries
#include <fstream>
#include <cctype> 
#include <queue> 

//json 
#include "include/json.hpp"
using json = nlohmann::json;

//File dependencies
#include "item.h"

bool ignore_var(string s){
    vector <string> ignored_variables = 
    {
    "equipment", "remaster", 
    };

    for (auto &i : ignored_variables) if (i == s) return true;
    return false; 
}

string temp; 

void initialize (json item, Item &newItem){
    for (auto &i : item.items()) //Individual Item 
    {
        if (ignore_var(i.key())) continue; 
        
        // Recursion // 
        if (i.value().is_object()) initialize (i.value(), newItem); // Recursive Call into SubObject
        
        // Hard Coded Data Entries //
        else if (i.key() == "name") newItem.setName(i.value());
        else if (i.key() == "source") newItem.addSource(i.value()); 
        else if (i.key() == "otherSources") newItem.addSource(i.value());
        else if (i.key() == "page") newItem.setPage(i.value()); 
        else if (i.key() == "level") newItem.setLevel(i.value());
        else if (i.key() == "amount") newItem.setPrice(i.value()); 
        else if (i.key() == "coin") newItem.setCoin(i.value()); 
        else if (i.value().is_boolean()) newItem.addTrait(i.key()); 
            
        // Cases of Possible Differing Data Types //
        else if (i.key() == "entries")  //There are sometimes sub-objects here, but we're choosing to ignore them
        {
            for (auto &j : i.value()) if (j.is_string()) newItem.addEntry(j); 
        }
        else if (i.key() == "bulk")
        {
            if (i.value().is_string())
            {
                if (i.value() == "L") newItem.setBulk(0.1); 
                else newItem.setBulk(0); 
            }
            else newItem.setBulk(i.value()); 
        }
        else if (i.key() == "hands")
        {
        if (i.value().is_string()) temp = i.value();
            else temp = to_string(i.value());
            temp += " hand(s)"; 
            newItem.addTrait(temp); 
            temp.clear(); 
        }

        // Trait Entries //
        else if (i.value().is_string()) newItem.addTrait(i.value()); 
        else if (i.value().is_array() && i.key() != "entries") //Array
        {
            for (auto &j : i.value())
            {
                if (j.is_string()) 
                {
                    if (i.key() == "Originally" || i.key() == "Reprinted") newItem.addSource(j);
                    else newItem.addTrait(j);
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

void read(){
    ifstream baseItems ("Input/baseitems.json");
    json input = json::parse(baseItems);
    vector <Item> items; 
    Item newItem;  
    int count = 0;

    for (auto &i : input) // Each Array is an Input File's set of Items 
    {
        for (auto &j : i.items()) // Contains Each Individual Item per Input File 
        { 
            initialize(j, newItem); // Called on Each Item, iterates through their Objects 
            items.push_back(newItem); 
            newItem.print(); 
            newItem.clear();
        }
    }
}