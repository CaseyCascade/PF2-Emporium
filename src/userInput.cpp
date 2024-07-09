#include "userInput.h"

// Utility
void UserInput :: clearScreen()
{
    #if defined(_WIN32) || defined(_WIN64)
        system("cls"); // Windows
    #else
        system("clear"); // Unix/Linux/Mac
    #endif
}; 
void UserInput :: printBanner()
{
    cout << R"(
 ____   __  ____  _  _  ____  __  __ _  ____  ____  ____    ____  ____    ____  _  _  ____   __  ____  __  _  _  _  _ 
(  _ \ / _\(_  _)/ )( \(  __)(  )(  ( \(    \(  __)(  _ \  (___ \(  __)  (  __)( \/ )(  _ \ /  \(  _ \(  )/ )( \( \/ )
 ) __//    \ )(  ) __ ( ) _)  )( /    / ) D ( ) _)  )   /   / __/ ) _)    ) _) / \/ \ ) __/(  O ))   / )( ) \/ (/ \/ \
(__)  \_/\_/(__) \_)(_/(__)  (__)\_)__)(____/(____)(__\_)  (____)(____)  (____)\_)(_/(__)   \__/(__\_)(__)\____/\_)(_/
)" << std::endl;
}
int UserInput :: convertToInt(const string& str) {
    int defaultValue = -1.0;
    try {
        return stof(str);
    } catch (const invalid_argument&) {
        cerr << "Invalid argument: " << str << endl;
    } catch (const out_of_range&) {
        cerr << "Out of range: " << str << endl;
    }
    return defaultValue;
}
// Generate from Shops
void UserInput :: listGeneration()
{
    clearScreen(); 
    command.displayShopList(); 
    cout << "Select a shop to view (0 to return): \n";
    getline(cin, input); 

    if (input == "0") startMenu(); 
    else if (convertToInt(input) == -1 or convertToInt(input) > command.getTemplateDatabase().size()) listGeneration(); 
    else viewShop(convertToInt(input)); 
}; 
void UserInput :: viewShop(int index) 
{
    clearScreen();
    command.viewShop(index - 1); 
    cout << "How many items would you like to generate? (0 to return): \n";
    getline(cin, input); 

    //ItemListGenerator generator; TODO

};

// Generate Shops (?)

// Create Shops
void UserInput :: shopCreation() {}; 
// Create Items
void UserInput :: itemCreation() {}; 
// Search Item
void UserInput :: itemSearch() {};
// Run
void UserInput :: startMenu()
{
    clearScreen(); 
    printBanner();
    cout << "Make a selection below:" << endl; 
    cout << "1. Generate Items from Shops\n"; 
    cout << "2. Create a Shop\n";
    cout << "3. Create an Item\n";
    cout << "4. Search an Item\n";

    getline(cin, input); 

    if (input == "1") listGeneration(); 
    else if (input == "2") shopCreation(); 
    else if (input == "3") itemCreation();
    else if (input == "4") itemSearch(); 
    else startMenu();
}; 