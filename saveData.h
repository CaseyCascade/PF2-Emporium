#include "item.h" 
#include <filesystem> 
using namespace std::filesystem; 

class SaveData {

    path inputPath = "input"; 
    path dataPath = "data"; 
    
    SaveData()
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
}; 