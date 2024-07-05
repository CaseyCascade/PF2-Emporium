#include "shopTemplate.h"

ShopTemplate :: ShopTemplate() {}; 
ShopTemplate :: ShopTemplate(vector <string> traits) 
{
    setWeights(traits); 
    setLevelRange(-1, 30); 
}; 
ShopTemplate :: ShopTemplate(vector <string> traits, int min, int max) 
{
    setWeights(traits);
    setLevelRange(min, max);
}; 
ShopTemplate :: ShopTemplate(vector <ShopTemplate> templates) 
{
    for (int i = 0; i < templates.size(); i++)
    {

    }
}; 

// Setters
void ShopTemplate :: setWeights(vector <string> traits) 
{
    int weight = 1; // This calculation may change
        for (auto& i : traits)
        {
            weightedTraits.push_back(make_pair(i, weight));
        }
}; 
void ShopTemplate :: setLevelRange(int min, int max) 
{
    levelMax = max; 
    levelMin = min;
};

// Getters 
vector <pair <string, int> > ShopTemplate :: getWeightedTraits() 
{
    return weightedTraits; 
}; 

vector <string> ShopTemplate :: getSourceBlacklist() 
{
    return sourceBlacklist; 
}; 
vector <string> ShopTemplate :: getTraitBlacklist() 
{
    return traitBlacklist; 
};

// Member Functions
bool ShopTemplate :: acceptLevel (int level) 
{
    if (levelMax < -10 || levelMin < -10)
        {
            cerr << "ERROR: Pattern level was not set" << endl;
            return false; 
        }
        else if (level <= levelMax && level >= levelMin) return true;
        else return false; 
};

ShopTemplate ShopTemplate :: combine (ShopTemplate templateOne, ShopTemplate templateTwo)
{
    
}; 

// Print
void ShopTemplate :: print() 
{
    cout << "--- Weighted Trait Table ---" << endl; 
        for (auto& i : weightedTraits)
        {
            cout << i.first << ": " << i.second << endl; 
        }
        cout << "--- Blacklisted Sources ---" << endl; 
        for (auto& i : sourceBlacklist)
        {
            cout << i << ", ";
        }
        cout << endl;
        cout << "--- Blacklisted Traits ---" << endl; 
        for (auto& i : traitBlacklist)
        {
            cout << i << ", ";
        }
        cout << endl; 
        cout << "Level Minimum: " << levelMin << endl; 
        cout << "Level Maximum: " << levelMax << endl; 
}; 