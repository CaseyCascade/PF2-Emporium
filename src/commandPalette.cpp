#include "commandPalette.h"

CommandPalette :: CommandPalette() {}; 

// Utility
bool CommandPalette :: isNumeric(const std::string& str) {
    return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}
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
void CommandPalette :: flattenArgs(queue <string>& tokens)
{
    queue <string> result;
    string arg;  
    while (!tokens.empty())
    {
        if (tokens.front() == "/")
        {
            arg.pop_back(); 
            result.push(arg); 
            arg.clear(); 
            tokens.pop(); 
        }
        else
        {
            arg += tokens.front() + " "; 
            tokens.pop();
        }
    }

    arg.pop_back(); 
    result.push(arg); 

    tokens = result; 
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
string CommandPalette :: border()
{
    return "\n= = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = = =\n\n"; 
};
void CommandPalette :: printColumns(const vector<string>& data, int numColumns) {
    if (data.empty()) return;

    vector <string> numberedList; 

    for (int i = 0; i < data.size(); i++)
    {
        numberedList.push_back(to_string(i+1) + ". " + data.at(i)); 
    }

    int numRows = numberedList.size();
    int numRowsPerColumn = (numRows + numColumns - 1) / numColumns;

    // Determine the maximum width for each column
    vector<int> columnWidths(numColumns, 0);
    for (int i = 0; i < numColumns; ++i) {
        for (int j = 0; j < numRowsPerColumn; ++j) {
            int index = j * numColumns + i;
            if (index < numberedList.size()) {
                columnWidths[i] = max(columnWidths[i], static_cast<int>(numberedList[index].length()));
            }
        }
    }

    // Print the data with uniform columns
    for (int i = 0; i < numRowsPerColumn; ++i) {
        for (int j = 0; j < numColumns; ++j) {
            int index = i * numColumns + j;
            if (index < numberedList.size()) {
                cout << setw(columnWidths[j] + 2) << left << numberedList[index];
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
void CommandPalette :: getInput()
{
    cout << "[>]: "; 
    getline(cin, input);
    transform(input.begin(), input.end(), input.begin(), [](unsigned char c) { return std::tolower(c); }); // Lowercasify input 
}

// Helper Functions
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
    int numColumns = 8;
    vector <string> list = database.getTraitDatabase();
    printColumns(list, numColumns);
    cout << border(); 
}; 
void CommandPalette :: listItems (queue <string> args) 
{
    filteredItemList.clear(); 
    vector <string> vec;

    flattenArgs(args);

    if (args.empty()) cout << "HUh" << endl; 

    while (!args.empty())
    {
        if (database.searchTraitDatabase(args.front()))
        {
            vec.push_back(args.front()); 
        } 
        args.pop(); 
    }

    if (vec.empty()) invalidInput();
    
    ShopTemplate list("TEMPORARY", vec);
    ScoredTable table(ptr, list);
    table.generate();
    vector <string> itemNames; 

    for (auto& i : table.getScoredTable())
    {
        if (i.second > 0)
        {
            filteredItemList.push_back(i.first); 
            itemNames.push_back(i.first.getName()); 
        }
    }
    cout << border(); 
    printColumns(itemNames, 4); 
    cout << border(); 
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

void CommandPalette :: generate(queue <string> args) 
{
    queue <string> originalArgs = args;
    flattenArgs(args); 

    string shopName = args.front();
    args.pop();

    if (!isNumeric(args.front())) invalidInput();
    int numItems = convertToInt(args.front()); 
    args.pop(); 
    
    

    filteredItemList = generateItemsFromShop(shopName, numItems); 
    vector <string> list;
    for (auto& i : filteredItemList) list.push_back(i.getName());
    cout << border();
    printColumns(list, 2);
    cout << border();  
    cout << "[r] to re-generate a new list. Enter a selection to view Item. [0] to continue: \n";
    getInput();
    queue <string> selection;
    selection.push(input);

    if (input == "r") generate(originalArgs);
    else if (input == "0") run(); 
    else lookupItem(selection);
};
void CommandPalette :: lookupShop(queue <string> args) 
{
    string shopName; 
    while (!args.empty())
    {
        shopName += args.front() + " "; 
        args.pop(); 
    }
    shopName.pop_back(); 
    cout << border();
    if (isNumeric(shopName) && convertToInt(shopName) <= database.getTemplateDatabase().size())
    {
        database.getTemplateDatabase().at(convertToInt(shopName)-1).print();
    }
    else if (database.getShop(shopName).getName() != "ERROR") database.getShop(shopName).print();
    else cerr << "Shop Not Found\n";
    cout << border();
};
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
    if (isNumeric(itemName) && convertToInt(itemName) <= filteredItemList.size())
    {
        filteredItemList.at(convertToInt(itemName)-1).print();
    }
    else if (isNumeric(itemName) && filteredItemList.empty())
    {
        cout << "Filter a list of items first using the list items command\n";
    }
    else if (database.getItem(itemName).getName() != "ERROR") database.getItem(itemName).print();
    else if (database.getItem(itemName).getName() == "ERROR") cerr << "Item Not Found\n";
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

void CommandPalette :: createShop() // TODO 
{}; 
void CommandPalette :: createItem() // TODO
{};
void CommandPalette :: createFork(queue <string> args) 
{
    string command = args.front();
    args.pop();
    if (command == "shop") createShop(); 
    else if (command == "item") createItem();
    else invalidInput();
}; 

void CommandPalette :: combine(queue <string> args) // TODO 
{

}; 
void CommandPalette :: reset() // TODO
{

}; 
void CommandPalette :: nuke() // TODO
{
    cout << border(); 
    cout << "ARE YOU SURE? This will delete all your custom entered data. Type DELETE to continue:\n";
    cout << "[>]: "; 
    getline(cin, input);
    if (input == "DELETE")
    {
        cout << "TODO\n"; 
    }
    else startup(); 

};  
void CommandPalette :: help() 
{
    cout << border();
    cout << "[h]    help                                            -- Displays a list of Commands\n";
    cout << "[c]    clear                                           -- Clear text from terminal\n"; 
    cout << "[lis]  list shops                                      -- Displays a list of all Shops\n";
    cout << "[lit]  list traits                                     -- Displays a list of all Traits\n";
    cout << "[lii]  list items     (TRAIT 1) / (TRAIT 2) / (..)     -- Displays a list of all Items with the specified Traits\n";
    cout << "[g]    generate       (SHOP NAME) / (# OF ITEMS)       -- Generates a random list of items from the shop specified\n";
    cout << "[lus]  lookup shop    (SHOP NAME)                      -- View the specified Shop\n";
    cout << "[lui]  lookup item    (ITEM NAME)                      -- View the specified Item\n";
    cout << "[cs]   create shop                                     -- Opens dialogue to create a new Shop\n";
    cout << "[ci]   create item                                     -- Opens dialogue to create a new Item\n";
    cout << "[co]   combine        (SHOP 1) / (SHOP 2) / (NAME)     -- Quickly creates a new shop by combining two shops together\n";
    cout << "[r]    reset                                           -- Delete and Reload all Core Items from JSON files\n";
    cout << "[q]    quit                                            -- close the program\n";
    cout << "       nuke                                            -- Delete all custom items and templates\n";
    cout << border(); 
}; 

// Driver
void CommandPalette :: runCommand (string command, queue <string> args) //TODO 
{
    if (command == "help" or command == "h") help(); 
    else if (command == "list") listFork(args); 
    else if (command == "lis") listShops(); 
    else if (command == "lit") listTraits();
    else if (command == "lii") listItems(args);
    else if (command == "generate" or command == "g") generate(args); 
    else if (command == "lookup") lookupFork(args);
    else if (command == "lus") lookupShop(args); 
    else if (command == "lui") lookupItem(args); 
    else if (command == "create") createFork(args);
    else if (command == "cs") createShop(); 
    else if (command == "ci") createItem();  
    else if (command == "combine" or command == "co") combine(args); 
    else if (command == "reset" or command == "r") reset(); 
    else if (command == "nuke") nuke(); 
    else if (command == "clear" or command == "c") 
    {
        clearScreen(); 
        startup(); 
    }
    else if (command == "quit" or command == "q") exit(0); 
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
        getInput();
        if (input.empty()) run();
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