#include "tableGenerator.h"

int main(){
    Database db;
    db.load_json_directory(); 
    db.print();

    ItemPattern pattern; 

    vector <string> vec = {"Shield"}; 
    
    pattern.set_weights(vec); 

    TableGenerator table (db, pattern);
}