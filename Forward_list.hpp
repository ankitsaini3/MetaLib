#pragma once

#include<cstddef>
#include<utility>
#include<iostream>
#include<new>

namespace MetaLib
{
    template <typename T>
    class forward_list
    {
        class Node
        {
        public:
            T value;
            Node* next;

            Node(): next{nullptr} {}
            Node(T val): value{val}, next{nullptr} {}
        };



        Node* headptr = nullptr;


    public:
        // default constructor
        forward_list()
        {
            headptr = nullptr;
        }

        // default destructor
        ~forward_list() noexcept
        {
            Node* cursor = headptr;

            while (headptr != nullptr)
            {
                headptr = headptr->next;
                delete cursor;
                cursor = headptr;
            }
        }

        // para ctor
        explicit forward_list(size_t n)
        {
            Node* cursor = new Node();
            headptr = cursor;

            for (size_t i = 1; i < n; i++)
            {
                cursor->next = new Node();
                cursor = cursor->next;
            }
        }

        //para ctor
        forward_list(size_t n, const T& value)
        {
            Node* cursor = new Node(value);
            headptr = cursor;

            for (size_t i = 1; i < n; i++)
            {
                cursor->next = new Node(value);
                cursor = cursor->next;
            }
        }

        // para ctor
        forward_list(const Node* begin, const Node* end)
        {

        }

        // initializer ctor
        forward_list(std::initializer_list<T> L)
        {
            Node* cursor = nullptr;
            headptr = nullptr;

            for (auto &i : L)
            {
                if (headptr == nullptr)
                {
                    headptr = new Node(i);
                    cursor = headptr;
                }
                else
                {
                    cursor->next = new Node(i);
                    cursor = cursor->next;
                }
                
            }
        }

        // copy ctor
        forward_list(const forward_list<T>& other)
        {
            if (other.headptr == nullptr)
            {
                headptr = nullptr;
                return;
            }

            Node* otherCursor = other.headptr;

            Node* thisCursor = new Node(otherCursor->value);
            headptr = thisCursor;
            otherCursor = otherCursor->next;

            while (otherCursor != nullptr)
            {
                thisCursor->next = new Node(otherCursor->value);
                thisCursor = thisCursor->next;
                otherCursor = otherCursor->next;
            }
        }

        // move ctor
        forward_list(forward_list<T>&& other) noexcept
        {
            headptr = other.headptr;
            other.headptr = nullptr;
        }

        // copy assignment
        forward_list<T>& operator=(const forward_list<T>& other)
        {
            Node* cursor = headptr;

            while (headptr != nullptr)
            {
                headptr = headptr->next;
                delete cursor;
                cursor = headptr;
            }

            Node* otherCursor = other.headptr;
            headptr = new Node(otherCursor->value);
            Node* thisCursor = headptr;

            while (cursor != nullptr)
            {
                thisCursor = new Node(otherCursor->value);
                thisCursor = thisCursor->next;
                otherCursor = otherCursor->next;
            }

            return *this;
        }

        // move assignment
        forward_list<T>& operator=(forward_list<T>&& other) noexcept
        {
            Node* cursor = headptr;

            while (headptr != nullptr)
            {
                headptr = headptr->next;
                delete cursor;
                cursor = headptr;
            }

            headptr = other.headptr;
            other.headptr = nullptr;
            
            return *this;
        }


        class Iterator
        {
            Node* ptr = nullptr;
        public:
            Iterator() {}
            Iterator(Node* ptrValue): ptr{ptrValue} {}

            Iterator& operator++()
            {
                ptr = ptr->next;
                return *this;
            }

            Iterator operator++(int)
            {
                Iterator temp = *this;
                ptr = ptr->next;
                return temp;
            }

            T& operator*()
            {
                return ptr->value;
            }

            bool operator==(const Iterator& other)
            {
                return this->ptr == other->ptr;
            }

            bool operator!=(const Iterator& other)
            {
                return this->ptr != other.ptr;
            }

            
        };


        Iterator begin()
        {
            return Iterator(headptr);
        }

        Iterator end()
        {
            return Iterator(nullptr);
        }

        Iterator begin() const
        {
            return Iterator(headptr);
        }

        Iterator end() const
        {
            return Iterator(nullptr);
        }

        
    };
}