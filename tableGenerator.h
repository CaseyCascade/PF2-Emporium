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

    void classifierCascade (Item current)
    {
        for (auto& blacklistedSource : pattern.getSourceBlacklist())
        {
            if (current.get_origin_source() == blacklistedSource)
            {
                //TODO
            }
        }
    }

    void generate ()
    {
        for (auto& item : pointerDatabase->get_items())
        {
            //TODO
        }
    }
        
};