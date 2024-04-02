#include "globals.h"

class trait {
    string data; 
    bool owned; 

    public:
    // CONSTRUCTORS //
    trait() {}
    trait (string s) {data = s; owned = false;}
    trait(string s, bool b) {data = s; owned = b;}

    // GET //
    string get_data() {return data;} 
    bool get_owned() {return owned;} 

    // SET // 
    void set(bool b) {owned = b;}  
};