#include "jsonParser.h"

class Database {
    vector <Item> database; 
    JsonParser parser; //TODO Eventually we will want to do this in another file entirely and decouple from database 

    path inputPath = "input"; 
    path dataPath = "data"; 

    public:
    Database()
    {}

    void print()
    {
        for (auto& i : database)
        {
            i.print(); 
        }
    }
    void load_json_directory () 
    {
        database.clear();
        vector <Item> contents;
        for (const auto& file : directory_iterator(inputPath))
        {
            contents = parser.read_from_json(file.path()); 
            database.insert(database.end(), contents.begin(), contents.end());
        }
    }
};