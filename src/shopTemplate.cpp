#include "shopTemplate.h"

ShopTemplate :: ShopTemplate() {}; 
ShopTemplate :: ShopTemplate(string errorMessage) 
{
    templateName = errorMessage; 
}; 
ShopTemplate :: ShopTemplate(string name, vector <string> traits) 
{
    templateName = name;  
    setDefaultWeights(traits); 
    setLevelRange(-1, 30); 
}; 
ShopTemplate :: ShopTemplate(string name, vector <string> traits, int min, int max) 
{
    templateName = name; 
    setDefaultWeights(traits);
    setLevelRange(min, max);
}; 
ShopTemplate :: ShopTemplate(string name, vector <string> traits, int min, int max, vector <string> blacklistSources, vector <string> blacklistTraits)
{
    templateName = name; 
    setDefaultWeights(traits); 
    setLevelRange(min, max);
    traitBlacklist = blacklistTraits;
    sourceBlacklist = blacklistSources; 
}
ShopTemplate :: ShopTemplate(string name, vector <ShopTemplate> templates) 
{
    templateName = name; 
    setLevelRange(-1, 30); 
    for (int i = 0; i < templates.size(); i++)
    {
        combine(templates.at(i)); 
    }
}; 

// Setters
void ShopTemplate :: setName(string name){templateName = name;}; 
void ShopTemplate :: addWeightedTrait (string trait, int weight){weightedTraits.push_back(make_pair(trait, weight));}; 
void ShopTemplate :: addBlacklistedSource(string source){sourceBlacklist.push_back(source);}; 
void ShopTemplate :: addBlacklistedTrait(string trait){traitBlacklist.push_back(trait);}; 
void ShopTemplate :: setLevelMin(int min)
{
    if (min >= MIN_LEVEL) levelMin = min;
}; 
void ShopTemplate :: setLevelMax(int max)
{
    if (max <= MAX_LEVEL) levelMax = max;
}; 
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
void ShopTemplate :: clear()
{
    templateName.clear(); 
    weightedTraits.clear(); 
    sourceBlacklist.clear(); 
    traitBlacklist.clear(); 
    levelMin = EMPTY; 
    levelMax = EMPTY; 
};
bool ShopTemplate :: enterData(string variable, string data)
{
    Item utility; 
    if (variable == "NAME") setName(data); 
    if (variable == "SOURCE BLACKLIST") addBlacklistedSource(data);
    if (variable == "TRAIT BLACKLIST") addBlacklistedTrait(data); 
    if (variable == "LEVEL MIN") setLevelMin(utility.convertToInt(data)); 
    if (variable == "LEVEL MAX") setLevelMax(utility.convertToInt(data)); 
    if (variable == "TRAITS") 
    {
        vector <string> tokens; 
        string token; 
        stringstream ss(data); 

        while (getline(ss, token, '|'))
        {
            tokens.push_back(token); 
        }
        if (tokens.size() != 2) 
        {
            cerr << "More than 2 Tokens in Trait Entry\n";
            return false; 
        } 
        addWeightedTrait(tokens.at(0), utility.convertToInt(tokens.at(1))); 
    }
    return true;  
}; 

// Getters 
string ShopTemplate :: getName()
{
    return templateName; 
};
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