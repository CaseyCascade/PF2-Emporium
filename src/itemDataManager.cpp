#include "itemDataManager.h"

ItemDataManager :: ItemDataManager () {}

string ItemDataManager :: getVariable(string line)
{
    vector <string> variables = {"NAME", "SOURCE", "PAGE", "GOLD", "LEVEL", "BULK", "ENTRY", "TRAITS"}; 
    for (auto& i : variables)
    {
        if (line == i) return i; 
        
    } 
    return "NONE"; 
}

vector <Item> ItemDataManager :: loadFile(string filepath)
{
    vector <Item> itemList; 
    Item newItem = Item();
    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filepath << endl; 
        return {Item("ERROR")}; 
    }

    string variable;
    string line; 
    while (getline(file, line))
    {
        if (line.empty())
        {
            itemList.push_back(newItem);
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
    return itemList; 
}

vector <Item> ItemDataManager :: load()
{
    vector <Item> allItems;
    vector <Item> tempItemList;  
    vector <fs::path> itemDirectories = {coreItemDirectory, customItemDirectory};
    for (auto& i : itemDirectories)
    {
        if (filesystem::exists(i) && filesystem::is_directory(i))
        {
            for (const auto& entry : filesystem::directory_iterator(i))
            {
                tempItemList = loadFile(entry.path().string());
                allItems.insert(allItems.end(), tempItemList.begin(), tempItemList.end()); 
            }
        }
    }
    return allItems;
}

void ItemDataManager :: saveCustomItems(vector <Item>, string filename) //TODO
{

}