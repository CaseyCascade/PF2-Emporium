#include "itemPattern.h"

class TableGenerator {
    Database* pointerDatabase; 
    // *allItems to access actual class
    //  allItems to access address
    ItemPattern pattern;

    vector <pair <Item, double> > scoredTable;

public:
    TableGenerator() {}
    TableGenerator (Database* global, ItemPattern p)
    {
        pointerDatabase = global;  
        pattern = p; 
    }

    bool early_reject (Item current)
    {
        for (auto& blacklisted : pattern.get_source_blacklist())
        {
            if (current.get_origin_source() == blacklisted) return true; // TODO Origin source always has a page # atm so this will fail every time
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

    void print()
    {
        print_table(scoredTable);
    }

    void generate ()
    {
        Item newItem;
        double score = -1.0;
        pair <Item, double> scoredItem = make_pair(newItem, score);
        

        for (auto& item : pointerDatabase->get_items())
        {
            scoredItem = make_pair(newItem, -1.0);

            if (early_reject(item)) continue; 
            score = calculate_score(item);
            if (score <= 0) continue;

            scoredItem = make_pair(item, score);
            scoredTable.push_back(scoredItem);
        }
        cout << "Table Size: " << scoredTable.size() << endl; 
        //mergesort(scoredTable, 0, scoredTable.size()-1);
        cout << "Table Size: " << scoredTable.size() << endl; 
    }
    void test () 
    {
        for (auto& item : pointerDatabase->get_items()) 
        {
            item.print(); 
        }
    }
};