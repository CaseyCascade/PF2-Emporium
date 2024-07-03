#include "item.h"

// Initialize & Setters
Item :: Item() {}
Item :: Item(string debugName)
{
    setName(debugName); 
}
void Item :: setName (string x){name = x;}
void Item :: setPage (int x) {page = x;}
void Item :: setGold (float x) {gold = x;}
void Item :: setLevel (int x) {level = x;}
void Item :: setBulk (float x) {bulk = x;}
void Item :: setSource (string x) {source = x;}
void Item :: setEntry (string x) {entry = x;}
void Item :: addTrait (string x) {traits.push_back(x);}

float Item :: convertToFloat(const string& str) {
    float defaultValue = -1.0;
    try {
        return stof(str);
    } catch (const invalid_argument&) {
        cerr << "Invalid argument: " << str << endl;
    } catch (const out_of_range&) {
        cerr << "Out of range: " << str << endl;
    }

    return defaultValue;
}

int Item:: convertToInt(const string& str) {
    return static_cast<int>(convertToFloat(str)); 
}

bool Item :: enterData (string variable, string data)
{
    if (variable == "GOLD" || variable == "BULK")
    {
        float convertedFloat = convertToFloat(data); 
        if (convertedFloat == -1.0)
        {
            cout << "Variable: " << variable << endl; 
            return false; 
        }
    }
    else if (variable == "PAGE" || variable == "LEVEL")
    {
        float convertedInt = convertToInt(data); 
        if (convertedInt == -1)
        {
            cout << "Variable: " << variable << endl; 
            return false; 
        }
    }
    else if (variable == "NAME") {setName(data);}
    else if (variable == "SOURCE") {setSource(data);}
    else if (variable == "ENTRY") {setEntry(data);}
    else if (variable == "TRAITS") {addTrait(data);}
    return true; 
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