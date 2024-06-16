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
    Item newItem; 
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
        variable = getVariable(line);
        while (getVariable(line) == "NONE")
        {
            getline(file, line); 
            newItem.enterData(variable, line); 
        }
        
    }
}
void Database :: load()
{

}