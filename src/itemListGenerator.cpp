#include "itemListGenerator.h"

// Constructor
ItemListGenerator :: ItemListGenerator(vector <pair <Item, int>> t, float p)
{
    scoredTable = t;  
    percentile = p; 
    target = scoredTable.size() * percentile;
}; 

// Getters
vector <int> ItemListGenerator :: getScoreRange()
{
    vector <int> range; 
    for (int i = 0; i < scoredTable.size(); i++)
    {
        if (!searchVector(range, scoredTable.at(i).second)) range.push_back(scoredTable.at(i).second);
    } 
    return range; 
}; 
int ItemListGenerator :: getAverage(vector <int> pickedNumbers)
{
    int sum = 0;
    for (auto& i : pickedNumbers)
    {
        sum += i; 
    }
    return sum / pickedNumbers.size(); 
}; 

// Member Functions
bool ItemListGenerator :: searchVector(vector <int> range, int n)
{
    for (auto& i : range) if (i == n) return true; 
    return false; 
}; 
void ItemListGenerator :: rubberbandRecursion(vector <int> &pickedNumbers, int N)
{
    random_device rd;
        mt19937 gen(rd());
        int random_number = -1;

        // Calculate our Average, and pick a number in a range so that we attempt to increase or decrease our average towards the target
        int average = getAverage(pickedNumbers);  
        printVector(pickedNumbers); 
        cout << "AVERAGE: " << average << endl; 
        while (true)
        {
            if (average <= target)
            {
                uniform_int_distribution<> distrib(target, scoredTable.size());
                random_number = distrib(gen);
            }
            else 
            {
                uniform_int_distribution<> distrib(0, target);
                random_number = distrib(gen);
            }
            if (!searchVector(pickedNumbers, random_number)) break; 
        }    

        pickedNumbers.push_back(random_number); 
        N--; 

        if (N == 0) return; 
        rubberbandRecursion(pickedNumbers, N); 
}; 
void ItemListGenerator :: rubberbandGenerator(int N)
{
    // Seed with a real random value, if available
    random_device rd;
    
    // Base Case
    mt19937 gen(rd());
    uniform_int_distribution<> distrib(0, scoredTable.size());
    int random_number = distrib(gen);
    pickedItemIndexes.push_back(random_number); 

    //Recursive Case
    rubberbandRecursion(pickedItemIndexes, N - 1);   

    if (debug) printResults();          
}; 


// Print
void ItemListGenerator :: printVector(vector <int> range)
{
    cout << "[";
    for (auto& i : range) cout << i << ", ";
    cout << "]" << endl; 
};
void ItemListGenerator :: printResults()
{
        cout << "Target: " << target << endl; 
        cout << "Average: " << getAverage(pickedItemIndexes) << endl; 
        printVector(pickedItemIndexes);

        cout << endl << "Picked Items: " << endl; 
        for (auto& i : pickedItemIndexes) cout << scoredTable.at(i).first.getName() << endl;  
}; 