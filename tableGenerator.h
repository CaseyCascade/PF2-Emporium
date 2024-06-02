#include "itemPattern.h"
#include <random>

class TableGenerator {
    Database* pointerDatabase; 
    ItemPattern pattern;

    vector <pair <Item, int> > scoredTable;

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

    int calculate_score (Item current)
    {
        int score = 0;  
        int i = 0; 
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
        int score = -1;
        pair <Item, int> scoredItem = make_pair(newItem, score);
        
        for (auto& item : pointerDatabase->get_items())
        {
            scoredItem = make_pair(newItem, -1.0);

            if (early_reject(item)) continue; 
            score = calculate_score(item);
            if (score <= 0) continue;

            scoredItem = make_pair(item, score);
            scoredTable.push_back(scoredItem);
        }
        countingSort(scoredTable);
    }

    void test () 
    {
        for (auto& item : pointerDatabase->get_items()) 
        {
            item.print(); 
        }
    }

    vector <pair <Item, int> > get_scored_table ()
    {
        return scoredTable; 
    }
};