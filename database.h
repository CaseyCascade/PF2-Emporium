#include "dataParser.h"

class Database {
    vector <Item> database; 
    DataParser parser;

    public:
    Database() // TODO DEBUG
    {
        database = parser.read_from_json("Input/baseitems.json");
    }

    void load () {}
    void save () 
    {
        string line; 
        for (auto i : database)
        {

        }
    }
    void update() {}
    void check_for_update() {}
};