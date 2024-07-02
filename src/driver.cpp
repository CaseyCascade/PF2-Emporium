#include <iostream>

#include "database.h"

using namespace std; 

int main ()
{
    Database db; 
    db.load(); 
    db.printTraits(); 
}