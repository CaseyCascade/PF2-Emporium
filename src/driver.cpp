#include <iostream>

#include "database.h"
#include "shopTemplate.h"
#include "scoredTable.h"


using namespace std; 

int main ()
{
    Database db;
    Database* ptr = &db; 
    db.load();

    vector <string> TL1 = {"dwarf", "weapon"};
    vector <string> TL2 = {"e", "rare", "magical"};

    vector <string> TB1 = {"evocation, weapon"}; 
    vector <string> TB2 = {"fatal", "e"};

    vector <string> SB1 = {"crb"};
    vector <string> SB2 = {"g&g"};

    ShopTemplate test1("Dwarf Weaponsmith", TL1, -1, 30, SB1, TB1);  
    ShopTemplate test2("Evil Magic", TL2, -1, 30, SB2, TB2); 

    ShopTemplate combined("Evil Dwarf Thaumaturgist", {test1, test2}); 

    ScoredTable table(ptr, combined);
    table.generate(); 
    table.print(); 
}