#include "database.h"

Database :: Database() {}

bool Database :: searchTraitDatabase(string s)
{
    for (auto &i : traitDatabase)
    {
        if (i == s) return true; 
    }
    return false; 
}

void Database :: setTraitDatabase()
{
    for (auto& item : itemDatabase)
    {
        for (auto& trait : item.getTraits())
        {
            if (!searchTraitDatabase(trait))
            {
                traitDatabase.push_back(trait); 
            }
        }
    }
}

void Database :: loadItems()
{
    ItemDataManager dataManager; 
    itemDatabase = dataManager.load(); 
}

void Database :: load()
{
    loadItems(); 
    //loadTemplates(); 
    setTraitDatabase(); 
}

void Database :: printTraits()
{
    for (auto& trait : traitDatabase)
    {
        cout << trait << endl; 
    }
}

void Database :: print()
{
    for (auto& item : itemDatabase)
    {
        cout << item.getName() << endl; 
    }
    cout << itemDatabase.size() << endl; 
}