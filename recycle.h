/*
struct globalID : private traitDB { //Holds the probability of rolling items of these global critieria 
    double level[20]; 
    double rarity[4]; 

    public: 
    globalID(){
        for (auto i : level){
            i = 0; 
        }
        for (auto i : rarity){
            i = 0; 
        }
    }
    void standardSkew(){

    }
    void strictSkew(){

    }
    void laxSkew(){

    }
};

void test()
{
    traitDB db; 
}

There are 3 types of trait sets that determine what item will occupy a slot
Strict indicates that the item MUST have ALL of the traits to be considered
Lax indicates the item FAVORS but does NOT REQUIRE any of the traits
Global gives necessary criteria that all items share (Level, Rarity, Cost, Bulk)
Exclude indicates the item MUST NOT have ANY of the traits. 


class probTable {
    private: 
    traitID empty; 
    globalID dfault; 
    tuple <traitID, traitID, traitID, globalID> table [maxSize]; //Enforced, Lax, Exclude, Global

    public:
    probTable()
    {
        for (auto i : table) 
        {
            i = make_tuple(empty, empty, empty, dfault);
        }
    }
    probTable(traitID strict, traitID lax, traitID exclude, globalID global){

    }
    void generate(){

    }
};
*/