#include "commandPalette.h"

CommandPalette :: CommandPalette() {}; 

// Getters
vector <ShopTemplate> CommandPalette :: getTemplateDatabase() 
{
    return database.getTemplateDatabase(); 
};

// Print
void CommandPalette :: viewShop(int index) 
{ 
    ShopTemplate shop = getTemplateDatabase().at(index);
    shop.print(); 
}; 
void CommandPalette :: displayShopList() 
{
    cout << "TODO" << endl; 
};
void CommandPalette :: displayTraits() {}; 