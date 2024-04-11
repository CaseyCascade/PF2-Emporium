#include <utility>
#include "tableSort.h"

class ItemPattern {
    vector <pair <string, double> > weightedTraits; 
    vector <string> sourceBlacklist; 
    vector <string> traitBlacklist; 
    int levelMin = -1;
    int levelMax = -1;

    public:
    ItemPattern () {}
    ItemPattern(vector <string> traits, int min, int max)
    {
        set_weights(traits);
        set_level_range(min, max);
    }
    void set_weights(vector <string> traits) 
    {
        double weight = 1; // This calculation may change TODO
        for (auto& i : traits)
        {
            weightedTraits.push_back(make_pair(i, weight));
        }
    }
    void set_level_range(int min, int max)
    {
        levelMax = max; 
        levelMin = min; 
    }

    vector <pair <string, double> > get_weighted_traits()
    {
        return weightedTraits; 
    }
    vector <string> get_source_blacklist ()
    {
        return sourceBlacklist;
    }
    vector <string> get_trait_blacklist()
    {
        return traitBlacklist; 
    }
    bool accept_level (int level) 
    {
        if (levelMax < 0 || levelMin < 0)
        {
            cerr << "ERROR: Pattern level was not set" << endl;
            return false; 
        }
        else if (level <= levelMax && level >= levelMin) return true;
        else return false; 
    }

    void print()
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
    }
};