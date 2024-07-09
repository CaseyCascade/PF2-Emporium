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
bool CommandPalette :: isAllUppercase(const string& str) 
{
    return all_of(str.begin(), str.end(), [](unsigned char c) {
        return isupper(c) || !isalpha(c); // Ignore non-alphabetic characters
    });
}
bool CommandPalette :: isAllLowercase(const string& str) 
{
    return all_of(str.begin(), str.end(), [](unsigned char c) {
        return islower(c) || !isalpha(c); // Ignore non-alphabetic characters
    });
}
queue <string> CommandPalette :: splitString(const string& str) 
{
    queue <string> tokens;
    istringstream iss(str);
    string token;
    
    while (iss >> token) {
        tokens.push(token);
    }
    return tokens;
}
bool CommandPalette :: isValidCommand (string str) 
{
    transform (str.begin(), str.end(), str.begin(), ::tolower); 
    for (auto& i : validCommands)
    {
        transform(i.begin(), i.end(), i.begin(), ::tolower); 
        if (str == i) return true; 
    }
    return false; 
};
string CommandPalette :: border()
{
    return "= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n"; 
};
void CommandPalette :: printColumns(const vector<vector<string>>& data) {
    if (data.empty()) return;

    // Determine the maximum width for each column
    vector<int> columnWidths(data[0].size(), 0);
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            columnWidths[i] = max(columnWidths[i], static_cast<int>(row[i].length()));
        }
    }

    // Print the data with uniform columns
    for (const auto& row : data) {
        for (size_t i = 0; i < row.size(); ++i) {
            cout << setw(columnWidths[i] + 2) << left << row[i];
        }
        cout << endl;
    }
}
vector<string> CommandPalette :: concatenate(const vector<string>& v1, const vector<string>& v2) {
    vector<string> result = v1;              // Copy the first vector
    result.insert(result.end(), v2.begin(), v2.end()); // Append the second vector
    return result;
}

// Getters
vector <ShopTemplate> CommandPalette :: getTemplateDatabase() 
{
    return database.getTemplateDatabase(); 
};

// Member Functions
vector <Item> CommandPalette :: generateItemsFromShop(string shop, int numItems)
{
    vector <Item> result; 
    ScoredTable table(ptr, database.getShop(shop));
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
)" << endl;
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
void CommandPalette :: displayTraits() // TODO Make a new function printTable(int numColumns, vector<vector<string>> list) to make the column number variable
{
    int numColumns = 3;
    vector <string> list = database.getTraitDatabase();
    vector<vector<string>> numberedList; 
    vector<vector<string>> newList; 
    for (int i = 0; i < list.size(); i++) numberedList.push_back({to_string(i+1) + ".", list.at(i)});

    for (int i = 0; i < numberedList.size() - 1; i = i+numColumns)
    {
        if (i == numberedList.size() - numColumns) newList.push_back(numberedList.at(i)); // Needs to concatenate remainder vectors 
        else newList.push_back(concatenate(numberedList.at(i), numberedList.at(i+1))); // Needs to account for more than 2 vectors
    }
    printColumns(newList); 
}; 

// Commands
void CommandPalette :: generate(string shop, int numItems) {};
void CommandPalette :: lookupShop(string str) 
{};
void CommandPalette :: lookupItem(string str)  {};
void CommandPalette :: create(bool shop, string name) {}; 
void CommandPalette :: combine(string shopOne, string shopTwo, string name) {};
void CommandPalette :: reset() {};  
void CommandPalette :: help() 
{
    cout << border();
    cout << "help                                       -- Displays a list of Commands\n";
    cout << "clear                                      -- Clear text from terminal\n"; 
    cout << "list shops                                 -- Displays a list of all Shops\n";
    cout << "list traits                                -- Displays a list of all Traits\n";
    cout << "list items     (TRAIT 1) (TRAIT 2) (..)    -- Displays a list of all Items with the specified Traits\n";
    cout << "generate       (SHOP NAME) (# OF ITEMS)    -- Generates a random list of items from the shop specified\n";
    cout << "lookup shop    (SHOP NAME)                 -- View the specified Shop\n";
    cout << "lookup item    (ITEM NAME)                 -- View the specified Item\n";
    cout << "create shop                                -- Opens dialogue to create a new Shop\n";
    cout << "create item                                -- Opens dialogue to create a new Item\n";
    cout << "combine        (SHOP 1) (SHOP 2) (NAME)    -- Quickly creates a new shop by combining two shops together\n";
    cout << "reset                                      -- Delete and Reload all Core Items from JSON files\n";
    cout << "nuke custom                                -- Delete all custom items and templates\n";
    cout << border(); 
}; 

// Driver
void CommandPalette :: runCommand (string command, queue <string> args) //TODO 
{
    if (command == "help") help(); 
    else if (command == "list shops") displayShopList(); 
    else if (command == "list traits") displayTraits(); 
    else if (command == "list items") return; 
    else if (command == "generate") return;  
    else if (command == "lookup shop") return;   
    else if (command == "lookup item") return;
    else if (command == "create shop") return;
    else if (command == "create item") return;
    else if (command == "combine") return;
    else if (command == "reset") return; 
    else if (command == "nuke custom") return; 
    else if (command == "clear") 
    {
        clearScreen(); 
        startup(); 
    }
};
void CommandPalette :: processLine (queue <string> tail) 
{
    string head = tail.front(); 
    tail.pop(); 

    if (isValidCommand(head)) runCommand(head, tail); // Hard coded to allow commands of 1 or 2 words. We can make a recursvie function if needed 
    else 
    {
        head += " " + tail.front(); 
        tail.pop();  
        if (isValidCommand(head)) runCommand(head, tail);
        else 
        {
            cerr << "Invalid Input. Type help for list of commands.\n";
            run(); 
        }
    }
};
void CommandPalette :: run()
{
    while (true)
    {
        getline(cin, input);
        processLine(splitString(input));  
    }
}; 
void CommandPalette :: startup() 
{
    clearScreen(); 
    displayBanner();
    cout << "Welcome to Emporium version " << version << "!\nType help for a list of commands: \n";  
    run(); 
}; 
