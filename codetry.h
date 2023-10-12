#ifndef CODETRY
#define CODETRY

#include<iostream>
using namespace std;

template<class elemType>
class linkList{

    private:
    struct node{
        elemType storage;
        node *p;
        
    };

    public:
    class Itr
    {
    private:
        node *rear;
    public:
        Itr(node *)
    };
    
    
};

#endif