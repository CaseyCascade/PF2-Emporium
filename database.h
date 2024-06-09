#include "jsonParser.h"

class Database {
    vector <Item> itemDatabase; 
    vector <string> traitDatabase; //TODO 

    JsonParser parser; //TODO Eventually we will want to do this in another file entirely and decouple from database 

    path inputPath = "input"; 
    path dataPath = "data"; 

    public:
    // Initialization //
    Database()
    {
        if (!exists(inputPath)) create_directory(inputPath); 
        if (!exists(dataPath)) create_directory(dataPath); 
    }
    bool search_directory(path directoryPath, string fileName)
    {
        path filePath = directoryPath / fileName;
        if (exists(directoryPath) && is_directory(directoryPath)) 
        { 
            for (const auto& entry : directory_iterator(directoryPath)) 
            { 
                if (entry.path() == filePath) return true;  
            }
            return false;  
        } 
        else 
        { 
            cerr << "Directory not found." << endl; 
        } 
    }
    bool in_trait_database(string s)
    {
        for (auto& i : traitDatabase)
        {
            if (i == s) return true; 
        }
        return false;
    }
    void initialize_trait_database()
    {
        for (auto& item : itemDatabase) { for (auto& trait : item.get_traits())
        {
            if (!in_trait_database(trait)) traitDatabase.push_back(trait);
        }}
    }
    void load_json_directory () 
    {
        vector <Item> contents;
        for (const auto& file : directory_iterator(inputPath))
        {
            if (file.path().extension().string() != ".json") continue; 
            contents = parser.read_from_json(file.path()); 
            itemDatabase.insert(itemDatabase.end(), contents.begin(), contents.end());
        }
        initialize_trait_database();
    }
    
    void print_items()
    {
        for (auto& item : itemDatabase) item.print(); 
    }
    void print_traits()
    {
        for (auto& trait : traitDatabase) 
        {
            cout << trait << endl; 
        }
    }
    // Getters //
    vector <Item> get_items()
    {
        return itemDatabase; 
    }

};