#include <iostream>

#include "./src/database.h"

using namespace std; 

int main ()
{
    Database db; 
    db.load(); 
    db.print(); 
}