#include "database.h"

Database :: Database() 
{
    load(); 
}

// Setters / Load
string Database :: trim(const std::string& str) 
{
    // Find the position of the first non-whitespace character
    auto start = str.begin();
    while (start != str.end() && std::isspace(*start)) {
        ++start;
    }

    // Find the position of the last non-whitespace character
    auto end = str.end();
    do {
        --end;
    } while (end != start && std::isspace(*end));

    // Return the trimmed string
    return std::string(start, end + 1);
}

void Database :: setTraitDatabase()
{
    for (auto& item : itemDatabase)
    {
        for (auto& trait : item.getTraits())
        {   
            trait = trim(trait); 
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
    fixTraits();
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
Item Database :: getItem(string name)
{
    transform(name.begin(), name.end(), name.begin(), ::tolower);

    for (auto& i : itemDatabase)
    {
        string itemName = i.getName(); 
        transform(itemName.begin(), itemName.end(), itemName.begin(), ::tolower);
        if (name == itemName) return i; 
    }
    cerr << "Item Not Found\n";
    return Item("ERROR"); 
}; 
ShopTemplate Database :: getShop (string name)
{
    transform(name.begin(), name.end(), name.begin(), ::tolower);

    for (auto& i : templateDatabase)
    {
        string shopName = i.getName(); 
        transform(shopName.begin(), shopName.end(), shopName.begin(), ::tolower);
        if (name == shopName) return i; 
    }
    cerr << "Shop Not Found\n";
    return ShopTemplate("ERROR"); 
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

bool Database :: searchVector(vector <string> vec, string s) 
{
    for (auto &i : vec)
    {
        if (i == s) return true; 
    }
    return false; 
};
void Database :: fixTraits()
{
    for (auto& i : traitDatabase)
    {
        if (i == "e") i = "evil";
        if (i == "g") i = "good";
        if (i == "n") i = "neutral";  
        if (i == "cn") i = "chaotic neutral";
        if (i == "ln") i = "lawful neutral";
        if (i == "cg") i = "chaotic good"; 
        if (i == "lg") i = "lawful good"; 
        if (i == "ce") i = "chaotic evil";
        if (i == "le") i = "lawful evil";
        if (i == "b") i = "bludgeoning"; 
        if (i == "s") i = "slashing"; 
        if (i == "p") i = "piercing"; 
        if (i == "1") i = "1 damage"; 
    }

    vector <string> newVector; 
    for (auto& i : traitDatabase)
    {
        i = trim(i); 
        if (!searchVector(newVector, i)) newVector.push_back(i); 
    }
    traitDatabase = newVector; 
}; 