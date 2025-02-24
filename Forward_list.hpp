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
        class node
        {
        public:
            T val;
            node* next;
        };


    public:
        // default constructor
        forward_list() noexcept
        {
            headptr = nullptr;
        }

        // default destructor
        ~forward_list()
        {
            
        }

        // para ctor
        explicit forward_list(size_t n)
        {

        }

        //para ctor
        forward_list(size_t n, const T& value)
        {

        }

        // para ctor
        forward_list(const node* begin, const node* end)
        {

        }

        // initializer ctor
        forward_list(std::initializer_list<T> L)
        {

        }

        // copy ctor
        forward_list(const forward_list<T>& other)
        {

        }

        // move ctor
        forward_list(const forward_list<T>&& other)
        {

        }

        // copy assignment
        forward_list<T>& operator=(const forward_list<T>& other)
        {

        }

        // move assignment
        forward_list<T>& operator=(const forward_list<T>&& other) noexcept
        {

        }


        

        
    };
}