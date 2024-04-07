#include "dataParser.h"
#include <filesystem>

using namespace std::filesystem; 

class Database {
    vector <Item> database; 
    DataParser parser; //TODO Eventually we will want to move this so that it is not including the JSON library until we need it to 

    path inputPath = "input"; 
    path dataPath = "data"; 

    public:
    Database() // TODO DEBUG
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