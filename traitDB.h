#include "globals.h"
#include "linklist.h"
#include <tuple> 

const int N = 5000; // Maximum Input Size 
const int SIZE = 1000; //Hash Table Size 

class traitDB {
    LL traitTable [SIZE]; 

    public: 
    // CONSTRUCTORS // TODO
    traitDB() {}

    // HASHING FUNCTIONS // TODO
    long long compute_hash(string const& s) 
    {
        const int p = 31;
        const int m = 1e9 + 9;
        long long hash_value = 0;
        long long p_pow = 1;
        for (char c : s) 
        {
            hash_value = (hash_value + (c - 'a' + 1) * p_pow) % m;
            p_pow = (p_pow * p) % m;
        }
        return hash_value;
    }
    int hash(string word)
    {
        int seed = 131; 
        unsigned long hash = 0;
        for(int i = 0; i < word.length(); i++){
            hash = (hash * seed) + word[i];
        }
        return hash % SIZE;
    }

    // SEARCH
    bool search (string s) 
    {
        if (traitTable[hash(s)].search(s)) return true; 
        else return false; 
    }

    // INSERT //
    void insert(string s){
        if (hash(s) > SIZE){
            cout << "ERROR: Hash function maps to " << hash(s) << endl; 
            return; 
        }
        if (!search(s))
        {
            traitTable[hash(s)].insert(s);  
        }
        return;
    }

    // LOAD / SAVE //
    void load () {}
    void save () {}
    void update() {}
    void check_for_update() {}

    // PERMISSIONS // 
    bool is_owned(string s){ if (search(s)) {return traitTable->getTrait(s).get_owned();} }
    void obtain(string s) {traitTable[hash(s)].getTrait(s).set(true);} 
    void remove(string s) {traitTable[hash(s)].getTrait(s).set(false);} 

    // DEBUG //
    void print()
    {
        for (int i = 0; i < SIZE; i++){
            cout << i << ": "; 
            traitTable[i].print(); 
        }
    }

};

traitDB known_traits; // Entire Database of Known Traits points here

class traitID : private traitDB { 
    traitDB* known = &known_traits; 

    public: 

    // CONSTRUCTOR // 
    traitID() {}
    // INITIALIZE // 
    void addTrait(string s)
    {
        if (known_traits.search(s)) obtain(s); 
        else 
        {
            known_traits.insert(s);
            obtain(s);  
        }
    }
    void removeTrait (string s) 
    {
        remove(s);
    }
    void clear()
    {

    }

    // CHECKS //
    bool has (string s) {return is_owned(s);}
};

void debug()
{
    traitDB db; 
}