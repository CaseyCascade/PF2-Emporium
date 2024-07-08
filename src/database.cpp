#include "database.h"

Database :: Database() {}

// Setters / Load
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
void Database :: loadTemplates() //TODO Not Implemented Yet
{
    ShopTemplateDataManager dataManager; 
    templateDatabase = dataManager.load(); 
}
void Database :: load()
{
    loadItems(); 
    setTraitDatabase();
    loadTemplates(); 
}

// Getters
vector <Item> Database :: getItemDatabase() 
{
    return itemDatabase; 
};
vector <string> Database :: getTraitDatabase()
{
    return traitDatabase; 
}; 
vector <ShopTemplate> Database :: getTemplateDatabase()
{
    return templateDatabase; 
};

// Member Functions
bool Database :: searchTraitDatabase(string s)
{
    for (auto &i : traitDatabase)
    {
        if (i == s) return true; 
    }
    return false; 
}

void Database :: printTraits()
{
    for (auto& trait : traitDatabase)
    {
        cout << trait << endl; 
    }
}

void Database :: printItems()
{
    for (auto& item : itemDatabase)
    {
        item.print();
    } 
}

void Database :: printTemplates() 
{
    for (auto& i : templateDatabase)
    {
        i.print(); 
    }
}