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
    return "\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n"; 
};
void CommandPalette :: printColumns(const vector<string>& data, int numColumns) {
    if (data.empty()) return;

    int numRows = data.size();
    int numRowsPerColumn = (numRows + numColumns - 1) / numColumns;

    // Determine the maximum width for each column
    vector<int> columnWidths(numColumns, 0);
    for (int i = 0; i < numColumns; ++i) {
        for (int j = 0; j < numRowsPerColumn; ++j) {
            int index = j * numColumns + i;
            if (index < data.size()) {
                columnWidths[i] = max(columnWidths[i], static_cast<int>(data[index].length()));
            }
        }
    }

    // Print the data with uniform columns
    for (int i = 0; i < numRowsPerColumn; ++i) {
        for (int j = 0; j < numColumns; ++j) {
            int index = i * numColumns + j;
            if (index < data.size()) {
                cout << setw(columnWidths[j] + 2) << left << data[index];
            }
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
void CommandPalette :: invalidInput()
{
    cout << "Invalid Input. Type help for a list of commands\n";
    run();  
}


// Commands
void CommandPalette :: listShops() 
{
    cout << border(); 
    int numColumns = 10; 
    vector <string> shopList; 
    for (auto& i : database.getTemplateDatabase())
    {
        shopList.push_back(i.getName());
    }
    printColumns(shopList, numColumns);
    cout << border(); 
};
void CommandPalette :: listTraits() 
{
    cout << border(); 
    int numColumns = 10;
    vector <string> list = database.getTraitDatabase();
    printColumns(list, numColumns);
    cout << border(); 
}; 
void CommandPalette :: listItems (queue <string> args) 
{
    cout << "TODO\n"; 
};
void CommandPalette :: listFork (queue <string> args) 
{
    string command = args.front();
    args.pop(); 

    if (command == "shops") listShops();
    else if (command == "traits") listTraits(); 
    else if (command == "items") listItems(args);
    else invalidInput();
}; 

void CommandPalette :: generate(queue <string> args) {};
void CommandPalette :: lookupShop(queue <string> args) 
{};
void CommandPalette :: lookupItem(queue <string> args)  
{
    string itemName; 
    while (!args.empty())
    {
        itemName += args.front() + " "; 
        args.pop(); 
    }
    itemName.pop_back(); 

    cout << border();
    database.getItem(itemName).print();
    cout << border();
};
void CommandPalette :: lookupFork(queue <string> args) 
{   
    string command = args.front();
    args.pop();
    if (command == "shop") return; 
    else if (command == "item") return;
    else invalidInput();
};

void CommandPalette :: createShop() {}; 
void CommandPalette :: createItem() {}; 
void CommandPalette :: createFork(queue <string> args) 
{
    string command = args.front();
    args.pop();
    if (command == "shop") createShop(); 
    else if (command == "item") createItem();
    else invalidInput();
}; 


void CommandPalette :: combine(queue <string> args) {};
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
    cout << "quit                                       -- close the program\n";
    cout << "nuke                                       -- Delete all custom items and templates\n";
    cout << border(); 
}; 

// Driver
void CommandPalette :: runCommand (string command, queue <string> args) //TODO 
{
    if (command == "help") help(); 
    else if (command == "list") listFork(args); 
    else if (command == "generate") return;  
    else if (command == "lookup") lookupFork(args);
    else if (command == "create") createFork(args); 
    else if (command == "combine") return;
    else if (command == "reset") return; 
    else if (command == "nuke") return; 
    else if (command == "clear") 
    {
        clearScreen(); 
        startup(); 
    }
    else if (command == "quit") exit(0); 
    else invalidInput(); 
};
void CommandPalette :: processLine (queue <string> args) 
{
    string command = args.front(); 
    args.pop(); 

    runCommand(command, args); // Hard coded to allow commands of 1 or 2 words. We can make a recursvie function if needed 
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
