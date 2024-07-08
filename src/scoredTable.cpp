#include "scoredTable.h"

// Constructors  
ScoredTable :: ScoredTable(){}; 
ScoredTable :: ScoredTable(Database* global, ShopTemplate shop)
{
    pointerDatabase = global; 
    shopTemplate = shop; 
};

// Getters
vector <pair <Item, int>> ScoredTable :: getScoredTable()
{
    return scoredTable; 
}; 

// Member Functions
void ScoredTable :: countingSort()
{
    vector<pair<Item,int>> arr = scoredTable; 

    // Find the maximum element in the array
    int maxElement = numeric_limits<int>::min();
    for (const auto& pair : arr)
        maxElement = max(maxElement, pair.second);

    // Create a count array to store the count of each element
    vector<int> count(static_cast<int>(maxElement) + 1, 0);

    // Count the occurrences of each element
    for (const auto& pair : arr)
        count[static_cast<int>(pair.second)]++;

    // Update the count array to store the actual position of each element
    for (int i = 1; i <= maxElement; ++i)
        count[i] += count[i - 1];

    // Create a temporary array to store the sorted output
    vector<pair<Item, int>> output(arr.size());

    // Build the sorted output array
    for (int i = arr.size() - 1; i >= 0; --i) {
        output[count[static_cast<int>(arr[i].second)] - 1] = arr[i];
        count[static_cast<int>(arr[i].second)]--;
    }

    // Copy the sorted output back to the original array
    for (int i = 0; i < scoredTable.size(); ++i)
        scoredTable[i] = output[i];
}; 
bool ScoredTable :: earlyReject(Item current)
{
    for (auto& blacklisted : shopTemplate.getSourceBlacklist())
        {
            if (current.getSource() == blacklisted) return true; // TODO Origin source always has a page # atm so this will fail every time
        }
        for (auto& blacklisted : shopTemplate.getTraitBlacklist())
        {
            if (current.searchTrait(blacklisted)) return true;
        }
        if (!shopTemplate.acceptLevel(current.getLevel())) return true;

        return false;
};
int ScoredTable :: calculateScore(Item current)
{
    int score = 0;  
    int i = 0; 
    for (auto& weightedTrait : shopTemplate.getWeightedTraits())
    {
        if (current.searchTrait(weightedTrait.first)) score += weightedTrait.second; 
    }
    return score;
}; 
void ScoredTable :: generate()
{
    Item newItem;
    int score = -1;
    pair <Item, int> scoredItem = make_pair(newItem, score);
    
    for (auto& item : pointerDatabase->getItemDatabase())
    {
        scoredItem = make_pair(newItem, -1.0);

        if (earlyReject(item)) continue; 
        score = calculateScore(item);
        if (score <= 0) continue;

        scoredItem = make_pair(item, score);
        scoredTable.push_back(scoredItem);
    }
    countingSort();
};

// Print
void ScoredTable :: print()
{
    for (auto& p : scoredTable) {
        cout << "(" << p.first.getName() << ", " << p.second << ") " << endl; 
    }
    cout << endl;
}; 