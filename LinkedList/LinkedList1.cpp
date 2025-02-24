#include<iostream>

class LinkedList1
{
    class Node
    {
    public:
        int value;
        Node* next;

        Node() {}
        Node(int val): value{val}, next{nullptr} {}
    };

    class Iterator
    {
        Node* ptr;
    public:
        Iterator(Node* node): ptr{node} {}


        bool operator ==(const Iterator& other)const ;
        bool operator !=(const Iterator& other) const ;
        void operator ++();
        int& operator*();
    };


    Node* headptr;

    Node* createNode(int value);
    void destroyNode(Node* nodePtr);
    
    public:
    LinkedList1();
    ~LinkedList1() noexcept;
    
    void insert(int index, int value);
    void remove(int index);
    Node* retrieveNode(int index);

    Iterator begin();
    Iterator end();
};


int main(int argc, char const *argv[])
{
    LinkedList1 list;

    

    list.insert(0,23);
    list.insert(1,45);
    list.insert(2,34);

    list.insert(0,0);

    list.remove(1);

    //  0, 45, 34 

    // for(auto it = list.begin(); it != list.end(); ++it)
    // {
    //     std::cout << *it << ", ";
    // }

    for(auto it: list)
    {
        std::cout << it << ", ";
    }
    
    return 0;
}


LinkedList1::LinkedList1(): headptr{nullptr}
{
}


LinkedList1::~LinkedList1()
{
    Node* cursor = headptr;

    while (headptr != nullptr)
    {
        headptr = headptr->next;
        destroyNode(cursor);
        cursor = headptr;
    }
}


void LinkedList1::insert(int index, int value)
{
    if (index < 0)
    {
        return;
    }
    
    Node* newNodeptr = createNode(value);

    if (index == 0)
    {
        newNodeptr->next = headptr;
        headptr = newNodeptr;
    }
    else
    {
        Node* cursor = retrieveNode(index-1);
    
        newNodeptr->next = cursor->next;
        cursor->next = newNodeptr;
    }
}

void LinkedList1::remove(int index)
{
    if (index < 0)
    {
        return;
    }

    if (index == 0)
    {
        Node* cursor = headptr;
        headptr = headptr->next;
        destroyNode(cursor);
    }
    else
    {
        Node* cursor = retrieveNode(index-1);
        Node* nodeToDestroyPtr = cursor->next;

        cursor->next = nodeToDestroyPtr->next;

        destroyNode(nodeToDestroyPtr);
    } 
}


LinkedList1::Node* LinkedList1::createNode(int value)
{
    Node* newNodePtr = new Node(value);
    return newNodePtr;
}

LinkedList1::Node* LinkedList1::retrieveNode(int index)
{
    Node* cursor = headptr;

    for (int i = 0; i < index; i++)
    {
        cursor = cursor->next;
        if (cursor == nullptr)
        {
            
        }
        
    }
    
    return cursor;
}

void LinkedList1::destroyNode(Node* nodePtr)
{
    delete nodePtr;
}


LinkedList1::Iterator LinkedList1::begin()
{
    return Iterator(headptr);
}


LinkedList1::Iterator LinkedList1::end()
{
    return Iterator(nullptr);
}


bool LinkedList1::Iterator::operator ==(const Iterator& other) const 
{
    return other.ptr == this->ptr;
}


bool LinkedList1::Iterator::operator !=(const Iterator& other) const
{
    return other.ptr != this->ptr;
}


void LinkedList1::Iterator::operator++()
{
    this->ptr = this->ptr->next;
}

int& LinkedList1::Iterator::operator*()
{
    return this->ptr->value;
}