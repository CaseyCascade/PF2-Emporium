#include "database.h"

Database :: Database() {}

string Database :: getVariable(string line)
{
    vector <string> variables = {"NAME", "SOURCE", "PAGE", "GOLD", "LEVEL", "BULK", "ENTRY", "TRAITS"}; 
    for (auto& i : variables)
    {
        if (line == i) return i; 
    } 
    return "NONE"; 
}
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
void Database :: loadFile(string filepath)
{
    Item newItem = Item();
    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filepath << endl; 
        return; 
    }

    string variable;
    string line; 
    while (getline(file, line))
    {
        if (line.empty())
        {
            itemDatabase.push_back(newItem);
            newItem.clear(); 
        }
        else if (getVariable(line) != "NONE")
        {
            variable = getVariable(line); 
        }
        else 
        {
            if (!newItem.enterData(variable, line)) cerr << "ITEM: " << newItem.getName() << endl;  
        }
    }
    file.close(); 
}

void Database :: load()
{
    for (auto& i : itemDirectories)
    {
        if (filesystem::exists(i) && filesystem::is_directory(i))
        {
            for (const auto& entry : filesystem::directory_iterator(i))
            {
                loadFile(entry.path().string()); 
            }
        }
    }
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