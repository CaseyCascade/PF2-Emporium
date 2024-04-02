#include <iostream>
#include "trait.h"
using namespace std;

struct Node {
    Node* next;
    trait ID; 

    Node() 
    {
        next = nullptr;
    }

    Node(trait x){
        ID = x;
        next = nullptr;
    }

    Node(trait x, Node* y){
        ID = x;
        next = y;
    }
};

struct LL {
    Node* root; 

    LL() {root = nullptr;}
    LL(Node* x) {root = x;}
    bool isEmpty(){
        if (root = nullptr) return true;
        else return false; 
    }

    void insert (string s){
        trait x (s); 
        Node* newNode = new Node(x);
        if (root == nullptr)
        { 
            root = newNode;
        }
        else 
        {
            Node* temp = root;
            while (temp->next != nullptr) //loops through list to find the final element, sets tempt to final 
            { 
                temp = temp->next;
            }
            temp->next = newNode; //Inserts new node where the nullptr was
        }
    }

    void delFirst(){
        Node* temp = root; 
        Node* t2;
        while (true){
            if (temp->next->next == nullptr){
                t2 = temp->next; 
                temp->next = nullptr;
                delete t2; 
                break; 
            }
            else temp = temp->next; 
        }
    }
    
    void delLast(){
        Node* temp = root;
        root = root->next; 
        delete temp; 
    }
    
    void print(){
        Node* temp = root; 
        while (temp != nullptr){
            cout << temp->ID.get_data() << " -> ";
            temp = temp->next;
        }
        cout << endl; 
    }

    bool search(string s)
    {
        Node* temp = root; 
        while (temp != nullptr){
            if (temp->ID.get_data() == s) return true; 
            temp = temp->next; 
        }
        return false; 
    }

    trait getTrait(string s)
    {
        Node* temp = root; 
        while (temp != nullptr){
            if (temp->ID.get_data() == s) return temp->ID; 
            temp = temp->next; 
        }
    }
};