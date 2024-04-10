#include <utility>
#include "item.h"

class ItemPattern {
    vector <pair <string, double> > weightedTraits; 
    pair <string, double> error = make_pair(string("ERROR"),0.0);
    vector <string> sourceBlacklist; 
    int levelMin; 
    int levelMax; 

    public:
    
    void setWeightedTraits()
    {

    }
    vector <string> getSourceBlacklist ()
    {
        return sourceBlacklist;
    }
};