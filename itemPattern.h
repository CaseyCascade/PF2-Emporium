#include <utility>
#include "item.h"

class ItemPattern {
    vector <pair <string, double> > weightedTraits; 
    pair <string, double> error = make_pair(string("ERROR"),0.0);
    vector <string> sourceBlacklist; 
    vector <string> traitBlacklist; 
    int levelMin; 
    int levelMax; 

    public:

    void set_weights()
    {

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