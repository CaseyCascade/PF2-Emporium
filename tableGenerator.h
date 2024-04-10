#include "itemPattern.h"

class TableGenerator {
    Database* pointerDatabase; 
    // *allItems to access actual class
    //  allItems to access address
    ItemPattern pattern;

    vector <pair <Item, double> > scoredTable;

public:
    TableGenerator() {}
    TableGenerator (Database& global, ItemPattern p)
    {
        pointerDatabase = &global;  
        pattern = p; 
    }

    bool early_reject (Item current)
    {
        for (auto& blacklisted : pattern.get_source_blacklist())
        {
            if (current.get_origin_source() == blacklisted) return true;
        }
        for (auto& blacklisted : pattern.get_trait_blacklist())
        {
            if (current.search_trait(blacklisted)) return true;
        }
        if (!pattern.accept_level(current.get_level())) return true;

        return false;
    }

    double calculate_score (Item current)
    {
        double score = 0;  
        for (auto& weightedTrait : pattern.get_weighted_traits())
        {
            if (current.search_trait(weightedTrait.first)) score += weightedTrait.second; 
        }
        return score;
    }

    void generate ()
    {
        pair <Item, double> scoredItem;

        for (auto& item : pointerDatabase->get_items())
        {
            if (early_reject(item)) continue; 
            scoredItem = make_pair(item, calculate_score(item));
            if (scoredItem.second < 0) continue;
            scoredTable.push_back(scoredItem);
        }
        mergesort(scoredTable, 0, scoredTable.size()-1);
    }
        
};