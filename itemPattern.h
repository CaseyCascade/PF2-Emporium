#include <utility>
#include "tableSort.h"

class ItemPattern {
    vector <pair <string, double> > weightedTraits; 
    pair <string, double> error = make_pair(string("ERROR"),0.0);
    vector <string> sourceBlacklist; 
    vector <string> traitBlacklist; 
    int levelMin; 
    int levelMax; 

    public:
    
    ItemPattern () {}
    void set_weights(vector <string> traits) //TODO for debugging
    {
        double weight = 1 / traits.size();
        for (auto& i : traits)
        {
            weightedTraits.push_back(make_pair(i, weight));
        }
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
        if (level <= levelMax && level >= levelMin) return true;
        else return false; 
    }
};