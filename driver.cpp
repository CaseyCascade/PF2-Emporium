#include "tableGenerator.h"

int main(){
    Database db;
    db.load_json_directory(); 

    vector <string> vec = {"dwarf", "Weapon", "B"}; 
    ItemPattern pattern(vec, 0, 20);


    TableGenerator table(&db, pattern);
    //table.test();
    table.generate(); 
    table.print();
}