#include "commandPalette.h"

CommandPalette :: CommandPalette() {}; 

// Utility
int CommandPalette :: convertToInt (const string& str) 
{
    int defaultValue = -1.0;
    try {
        return stof(str);
    } catch (const invalid_argument&) {
        cerr << "Invalid argument: " << str << endl;
    } catch (const out_of_range&) {
        cerr << "Out of range: " << str << endl;
    }
    return defaultValue;
}; 
bool CommandPalette :: isAllUppercase(const std::string& str) 
{
    return std::all_of(str.begin(), str.end(), [](unsigned char c) {
        return std::isupper(c) || !std::isalpha(c); // Ignore non-alphabetic characters
    });
}
bool CommandPalette :: isAllLowercase(const std::string& str) 
{
    return std::all_of(str.begin(), str.end(), [](unsigned char c) {
        return std::islower(c) || !std::isalpha(c); // Ignore non-alphabetic characters
    });
}

// Getters
vector <ShopTemplate> CommandPalette :: getTemplateDatabase() 
{
    return database.getTemplateDatabase(); 
};

// Member Functions
vector <Item> CommandPalette :: generateItemsFromShop(int shopIndex, int numItems)
{
    vector <Item> result; 
    ScoredTable table(ptr, database.getTemplateDatabase().at(shopIndex));
    table.generate();
    ItemListGenerator generator(table.getScoredTable(), 0.7);
    generator.rubberbandGenerator(numItems);
    
    for (auto& i : generator.getPickedItemIndexes())
    {
        result.push_back(table.getScoredTable().at(i).first);
    }
    return result; 
};

Item CommandPalette :: itemLookup(string itemName)
{
    return database.getItem(itemName);
};

// Print
void CommandPalette :: clearScreen()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux/Mac
    #endif
}; 
void CommandPalette :: displayBanner()
{
    cout << R"(
 ____   __  ____  _  _  ____  __  __ _  ____  ____  ____    ____  ____    ____  _  _  ____   __  ____  __  _  _  _  _ 
(  _ \ / _\(_  _)/ )( \(  __)(  )(  ( \(    \(  __)(  _ \  (___ \(  __)  (  __)( \/ )(  _ \ /  \(  _ \(  )/ )( \( \/ )
 ) __//    \ )(  ) __ ( ) _)  )( /    / ) D ( ) _)  )   /   / __/ ) _)    ) _) / \/ \ ) __/(  O ))   / )( ) \/ (/ \/ \
(__)  \_/\_/(__) \_)(_/(__)  (__)\_)__)(____/(____)(__\_)  (____)(____)  (____)\_)(_/(__)   \__/(__\_)(__)\____/\_)(_/
)" << std::endl;
}

void CommandPalette :: viewShop(int index) 
{ 
    ShopTemplate shop = getTemplateDatabase().at(index);
    shop.print(); 
}; 
void CommandPalette :: displayShopList() 
{
    cerr << "TODO\n"; 
};
void CommandPalette :: displayTraits() {}; 

// Commands
void CommandPalette :: generate(string shop, int numItems) {};
void CommandPalette :: lookup(string str) 
{
    if (isAllLowercase(str)) // Lookup Item
    {
        database.getItem(str).print(); 
    }
    if (isAllUppercase(str)) // Lookup Shop
    {
        database.getShop(str).print(); 
    }
}; 
void CommandPalette :: create(bool shop, string name) {}; 
void CommandPalette :: combine(string shopOne, string shopTwo, string name) {};
void CommandPalette :: reset() {};  
void CommandPalette :: help() {}; 

// Input Parsing 
void CommandPalette :: runCommand (string command) {};
void CommandPalette :: processLine (string line) {};  
void CommandPalette :: run() {}; 
