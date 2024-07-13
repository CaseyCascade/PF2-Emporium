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

void ItemDataManager :: saveCustomItems(vector <Item> items, string filename) //TODO
{
    filesystem :: path file(filename + ".txt");
    filesystem :: path fullPath(customItemDirectory / file); 
    ofstream fout; 
    fout.open(fullPath, ios::in|ios::out|ios::app); // Appends file instead of overwriting it
    if (!fout)
    {
        cerr << "Error opening file\n";
        exit(0);
    }
    for (auto& item : items) 
    {
        fout << "NAME" << endl; 
        fout << item.getName() << endl; 
        fout << "SOURCE\n";
        fout << item.getSource();
        fout << "PAGE\n";
        fout << item.getPage();
        fout << "GOLD\n";
        fout << item.getGold();
        fout << "LEVEL\n";
        fout << item.getLevel();
        fout << "BULK\n";
        fout << item.getBulk();
        fout << "ENTRY\n";
        fout << item.getEntry();
        fout << "TRAITS\n"; 
        for (auto& trait : item.getTraits())
        {
            fout << trait << endl;
        }
       fout << endl; 
    }
    fout.close(); 
}