#include "item.h"

// Initialize & Setters
Item :: Item() {}
void Item :: setName (string x){name = x;}
void Item :: setPage (int x) {page = x;}
void Item :: setGold (float x) {gold = x;}
void Item :: setLevel (int x) {level = x;}
void Item :: setBulk (float x) {bulk = x;}
void Item :: setSource (string x) {source = x;}
void Item :: setEntry (string x) {entry = x;}
void Item :: addTrait (string x) {traits.push_back(x);}
void Item :: enterData (string variable, string data)
{
    if (variable == "NAME") {setName(data);}
    else if (variable == "PAGE") {setPage(stoi(data));}
    else if (variable == "GOLD") {setGold(stof(data));}
    else if (variable == "LEVEL") {setLevel(stoi(data));}
    else if (variable == "BULK") {setBulk(stof(data));}
    else if (variable == "SOURCE") {setSource(data);}
    else if (variable == "ENTRY") {setEntry(data);}
    else if (variable == "TRAITS") {addTrait(data);}
}

// Getters
string Item :: getName () {return name;}
int Item :: getPage () {return page;}
float Item :: getGold () {return gold;}
int Item :: getLevel () {return level;}
float Item :: getBulk () {return bulk;}
string Item :: getSource () {return source;}
string Item :: getEntry () {return entry;}
vector <string> Item :: getTraits () {return traits;}

// Other
void Item :: clear () 
{
    setName("NONE");
    setPage(0);
    setGold(0.0);
    setLevel(0);
    setBulk(0.0);
    setSource("NONE");
    setEntry("NONE");
    traits.clear(); 
}