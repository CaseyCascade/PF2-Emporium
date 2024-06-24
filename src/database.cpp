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
            newItem.enterData(variable, line); 
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
}

void Database :: print()
{
    cout << itemDatabase.size() << endl; 
    for (auto& item : itemDatabase)
    {
        cout << item.getName() << endl; 
    }
}