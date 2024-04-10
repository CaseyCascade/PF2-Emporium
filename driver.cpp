#include "tableGenerator.h"

int main(){
    Database db;
    db.load_json_directory(); 
    //db.print();

    vector <string> vec = {"Shield"}; 
    ItemPattern pattern(vec, 0, 20);


    TableGenerator table(&db, pattern);
    //table.test();
    table.generate(); 
    table.print();
}