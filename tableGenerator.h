#include "database.h"
#include "itemPattern.h"

class TableGenerator {
    Database* pointerDatabase; 
    // *allItems to access actual class
    //  allItems to access address
    ItemPattern pattern;

    vector <pair <Item, double> > scoredTable;

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
    }

    void calculate_score (Item current)
    {
        double score; 

        
    }

    void generate ()
    {
        for (auto& item : pointerDatabase->get_items())
        {
            if (early_reject(item)) continue; 
            
        }
    }
        
};