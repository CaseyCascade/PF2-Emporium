#include "randomItemPicker.h"

int main(){
    Database db;
    db.load_json_directory(); 
    //db.print_traits();
    vector <string> vec = {"DWARF", "WEAPON", "B"}; 
    ItemPattern pattern(vec, 0, 20);


    TableGenerator table(&db, pattern);
    table.generate(); 

    RandomItemPicker picker(table.get_scored_table(), 0.75); 
    picker.rubberband_generator(10);
}