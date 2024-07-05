#include "shopTemplate.h"

ShopTemplate :: ShopTemplate() {}; 
ShopTemplate :: ShopTemplate(vector <string> traits) 
{
    setDefaultWeights(traits); 
    setLevelRange(-1, 30); 
}; 
ShopTemplate :: ShopTemplate(vector <string> traits, int min, int max) 
{
    setDefaultWeights(traits);
    setLevelRange(min, max);
}; 
ShopTemplate :: ShopTemplate(vector <string> traits, int min, int max, vector <string> blacklistSources, vector <string> blacklistTraits)
{
    setDefaultWeights(traits); 
    setLevelRange(min, max);
    traitBlacklist = blacklistTraits;
    sourceBlacklist = blacklistSources; 
}
ShopTemplate :: ShopTemplate(vector <ShopTemplate> templates) 
{
    setLevelRange(-1, 30); 
    for (int i = 0; i < templates.size(); i++)
    {
        combine(templates.at(i)); 
    }
}; 

// Setters
void ShopTemplate :: setDefaultWeights(vector <string> traits) 
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
int ShopTemplate :: getLevelMin()
{
    return levelMin; 
};
int ShopTemplate :: getLevelMax()
{
    return levelMax; 
}; 
bool ShopTemplate :: isDefaultLevelRange()
{
    if (levelMin != MIN_LEVEL and levelMax != MAX_LEVEL) return false; 
    else return true; 
};
bool ShopTemplate :: isBlacklisted (string s)
{
    for (auto& i : traitBlacklist) if (s == i) return true; 
    for (auto& i : sourceBlacklist) if (s == i) return true; 
    return false; 
};
int ShopTemplate :: searchTrait(string trait) 
{
    cout << "";
    for (int i = 1; i < weightedTraits.size(); i++)
    {
        if (weightedTraits.at(i - 1).first == trait) return i; // Returns position in vector starting at 1, or 0 if it doesn't exist 
    } 
    return 0; 
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

void ShopTemplate :: deleteTrait(string trait) // This is ridiculously inefficient but it shouldn't be much of a problem 
{
    vector<pair<string,int>> newVec; 
    for (auto& pair : weightedTraits)
    {
        if (pair.first != trait)
        {
            newVec.push_back(pair); 
        }
    }
    weightedTraits = newVec; 
}; 

void ShopTemplate :: removeBlacklistedTraits()
{
    for (auto& trait : traitBlacklist)
    {
        if (searchTrait(trait)) deleteTrait(trait); 
    }
};

void ShopTemplate :: combine (ShopTemplate &templateTwo)
{ 
    // Handling Level Range (Only one in the list can be non-EMPTY)
    if (this->isDefaultLevelRange())
    {
        if (!templateTwo.isDefaultLevelRange()) 
            this->setLevelRange(templateTwo.getLevelMin(), templateTwo.getLevelMax()); 
    }
    else if (!templateTwo.isDefaultLevelRange()) 
    {
        cerr << "Level Range Conflict in ShopTemplate combine()\n"; 
        cerr << templateTwo.getLevelMin() << " " << templateTwo.getLevelMax() << endl; 
    }

    // Handling Blacklist
    for (auto& trait : templateTwo.getTraitBlacklist())
    {
        if (!isBlacklisted(trait)) traitBlacklist.push_back(trait); 
    }
    for (auto& source : templateTwo.getSourceBlacklist())
    {
        if (!isBlacklisted(source)) sourceBlacklist.push_back(source); 
    }

    // Handling Weighted Trait List
    int indexPlusOne = 0; 

    for (auto& i : weightedTraits)
    {
        //cout << i.first << endl; 
        indexPlusOne = templateTwo.searchTrait(i.first); // Returns False if the trait isn't in the vector. Otherwise returns the index + 1; 
        if (indexPlusOne) // Gets the average of the two scores if the traits both exist 
        { 
            i.second = (i.second + templateTwo.getWeightedTraits().at(indexPlusOne - 1).second) / 2; 
            templateTwo.getWeightedTraits().erase(templateTwo.getWeightedTraits().begin() + (indexPlusOne - 1));
        }
    }
    for (const auto& i : templateTwo.getWeightedTraits())
    {
        //cout << i.first << endl; 
        weightedTraits.push_back(i); 
    }

    // Finally, cull all traits that are blacklisted 
    removeBlacklistedTraits(); 
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