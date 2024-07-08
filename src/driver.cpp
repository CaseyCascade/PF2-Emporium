#include <iostream>

#include "database.h"
#include "shopTemplate.h"
#include "scoredTable.h"
#include "itemListGenerator.h"

using namespace std; 

int main ()
{
    Database db;
    Database* ptr = &db; 
    db.load();

    vector <string> TL1 = {"dwarf", "weapon", "b"};

    ShopTemplate test("Dwarf Weaponsmith", TL1);  

    ScoredTable table(ptr, test);
    table.generate(); 
    table.print(); 
    
    ItemListGenerator generator(table.getScoredTable(), 0.7);
    generator.rubberbandGenerator(10); 
}