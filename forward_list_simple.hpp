#ifndef forward_list_simple_h
#define forward_list_simple_h
#include<iostream>

class MyClass
{
    int *p;
public:
    MyClass()
    {
        std::cout << "ctor of My Class called\n";
        p = new int[5];
    }

    ~MyClass()
    {
        std::cout << "dtor of MyCLass called\n";
        delete [] p;
    }
};

class LinkedList
{
    class Node
    {

    };
};

#endif