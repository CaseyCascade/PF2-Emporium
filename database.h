#include "jsonParser.h"
#include <filesystem>

using namespace std::filesystem; 

class Database {
    vector <Item> database; 
    JsonParser parser; //TODO Eventually we will want to do this in another file entirely and decouple from database 

    path inputPath = "input"; 
    path dataPath = "data"; 

    public:
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
    void json_to_txt () 
    {
        vector <Item> contents;
        for (const auto& file : directory_iterator(inputPath))
        {
            contents = parser.read_from_json(file.path()); 
        }
    }
};