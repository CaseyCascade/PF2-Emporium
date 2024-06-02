#include "randomItemPicker.h"

int main(){
    Database db;
    db.load_json_directory(); 
    //db.print_traits();
    vector <string> vec = {"DWARF", "WEAPON", "B"}; 
    ItemPattern pattern(vec, 0, 20);


    TableGenerator table(&db, pattern);
    table.generate(); 
    //table.print();

    RandomItemPicker picker(table.get_scored_table()); 
    picker.rubberband_generator(10, 0.75);
}