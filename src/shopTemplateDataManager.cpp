#include "shopTemplateDataManager.h"

// Constructor
ShopTemplateDataManager :: ShopTemplateDataManager() {};

// Member Variables 
string ShopTemplateDataManager :: getVariable(string line) 
{
    vector <string> variables = {"NAME", "TRAITS", "SOURCE BLACKLIST", "TRAIT BLACKLIST", "LEVEL MIN", "LEVEL MAX", "CUSTOM"}; 
    for (auto& i : variables)
    {
        if (line == i) return i; 
        
    } 
    return "NONE"; 
}; 
vector <ShopTemplate> ShopTemplateDataManager :: loadFile (string filepath) 
{
    vector <ShopTemplate> templateList; 
    ShopTemplate newTemplate = ShopTemplate();
    ifstream file(filepath);
    if (!file.is_open())
    {
        cerr << "Error opening file: " << filepath << endl; 
        return {ShopTemplate("ERROR")}; 
    }

    string variable;
    string line; 
    while (getline(file, line))
    {
        if (line.empty())
        {
            templateList.push_back(newTemplate);
            newTemplate.clear(); 
        }
        else if (getVariable(line) != "NONE")
        {
            variable = getVariable(line); 
        }
        else 
        {
            if (!newTemplate.enterData(variable, line)) cerr << "TEMPLATE: " << newTemplate.getName() << endl;  
        }
    }
    file.close(); 
    return templateList; 
}; 

vector <ShopTemplate> ShopTemplateDataManager :: load() 
{
    vector <ShopTemplate> allTemplates;
    vector <ShopTemplate> tempTemplateList;  
    vector <fs::path> templateDirectories = {coreTemplateDirectory, customTemplateDirectory};
    for (auto& i : templateDirectories)
    {
        if (filesystem::exists(i) && filesystem::is_directory(i))
        {
            for (const auto& entry : filesystem::directory_iterator(i))
            {
                tempTemplateList = loadFile(entry.path().string());
                allTemplates.insert(allTemplates.end(), tempTemplateList.begin(), tempTemplateList.end()); 
            }
        }
    }
    return allTemplates;
}; 
void ShopTemplateDataManager :: writeTemplatesToFile(string filename, vector <ShopTemplate>, bool custom) // TODO 
{};