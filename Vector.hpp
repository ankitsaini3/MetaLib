#pragma once 

#include <cstddef>
#include <utility>
#include<iostream>
#include <new>
// need template for vector<int>, vector<double> etc.
// need dynamic array for underlying storage 

namespace MetaLib
{
   template <typename T>
    class vector
    {
    private:
        T* array;

        size_t reservedSize = 0;
        size_t vectorSize = 0;

        inline void reallocate()
        {
            T* tempArray = reinterpret_cast<T*>(new char[reservedSize * sizeof(T)]);

            for (size_t i = 0; i < vectorSize; i++)
            {
                new (tempArray+i) T(std::move(array[i]));
            }

            for (size_t i = 0; i < vectorSize; i++)
            {
                array[i].~T();
            }
            
            delete [] reinterpret_cast<char*>(array);

            array = tempArray;
        
        }


    public:
        
        // default constructor
        vector() noexcept
        {
            std::cout << "default constructor called "<< this <<"\n";
            array = reinterpret_cast<T*>(new char[reservedSize * sizeof(T)]);
        }


        // default destructor
        ~vector() noexcept
        {
            std::cout << "default destructor called" << this <<"\n";

            for (size_t i = 0; i < vectorSize; ++i)
            {
                array[i].~T();
            }

            delete [] reinterpret_cast<char *>(array);
            
        }

        

        explicit vector(size_t n): reservedSize(n), vectorSize(n)
        {
            std::cout << "parameterized constructor (size_t n) called " <<this<<"\n";

            array = reinterpret_cast<T*>(new char[reservedSize * sizeof(T)]);

            for (size_t i = 0; i < vectorSize; i++)
            {
                new (array + i) T();
            }
        }

        
        vector(size_t n, const T& value): reservedSize(n), vectorSize(n)
        {
            std::cout << "parameterized constructor (size_t n, const T& value) called\n";

            array = reinterpret_cast<T*>(new char[reservedSize * sizeof(T)]);

            for (size_t i = 0; i < vectorSize; i++)
            {
                new (array + i) T(value);
            }
        }

        vector(const T* first, const T* last): reservedSize(last - first), vectorSize(reservedSize)
        {
            array = reinterpret_cast<T*>(new char[reservedSize * sizeof(T)]);

            for (size_t i = 0; i < vectorSize; ++i, ++first)
            {
                T* temp = reinterpret_cast<T*>(array) + i;
                new (temp) T (*first);
            }
            
        }

        // initializer list constructor 
        vector(std::initializer_list<T> L): reservedSize(L.size())
        {

            std::cout << "initializer list constructor called" << this <<"\n";

            array = reinterpret_cast<T*>(new char[reservedSize * sizeof(T)]);

            for (auto &v : L)
            {
                new  (array + vectorSize) T(v);
                ++vectorSize;
            }
            
        }


        // copy constructor
        vector(const vector<T>& other): reservedSize(other.reservedSize), vectorSize(other.vectorSize)
        {

            std::cout << "copy constructor called " << this << "\n";

            array = reinterpret_cast<T*>(new char[reservedSize * sizeof(T)]);

            for (size_t i = 0; i < vectorSize; ++i)
            {
                new (array + i) T(other[i]);
            }
        }


        // move constructor
        vector(vector<T> &&temp) noexcept:
            array(temp.array), vectorSize(temp.vectorSize), 
            reservedSize(temp.reservedSize)
        {
            std::cout << "move constructor called\n";
            temp.array = nullptr;
            temp.vectorSize = temp.reservedSize = 0;
        }

    
        // copy assignment
        vector<T>& operator=(const vector<T> &other)
        {

            std::cout << "copy assignment called\n";

            if(this == &other)
            {
                return *this;
            }

            if (other.vectorSize > this->vectorSize)
            {
                T *tempArray = reinterpret_cast<T*>(new char[other.reservedSize * sizeof(T)]);

                for (size_t i = 0; i < other.vectorSize; i++)
                {
                    new (tempArray + i) T(other[i]);
                }

                for (size_t i = 0; i < vectorSize; i++)
                {
                    reinterpret_cast<T*>(array)[i].~T();
                }

                delete [] reinterpret_cast<char*>(array);
                
                array = reinterpret_cast<T*>(tempArray);

                vectorSize = other.vectorSize;
                reservedSize = other.reservedSize;
                
            }
            else
            {
                for (size_t i = 0; i < other.vectorSize; i++)
                {
                    this->operator[](i) = other[i];
                }

                for (size_t i = other.vectorSize; i < vectorSize; i++)
                {
                    reinterpret_cast<T*>(array)[i].~T();
                }
                
                vectorSize = other.vectorSize;
                reservedSize = other.reservedSize;

                reallocate();
            }

            return *this;
            
        }


        // move assignment
        vector<T>& operator=(vector<T>&& other) noexcept
        {
            std::cout << "Move assignment called\n";
            
            if (this == &other)
            {
                return *this;
            }

            for (size_t i = 0; i < reservedSize; ++i)
            {
                array[i].~T();
            }

            delete [] reinterpret_cast<char *>(array);

            array = other.array;
            vectorSize = other.vectorSize;
            reservedSize = other.reservedSize;

            other.array = nullptr;
            other.vectorSize = 0;
            other.reservedSize = 0;

            return *this;
        }


        bool operator==(const vector<T> &other) const
        {
            if (vectorSize != other.vectorSize)
            {
                return false;
            }

            for (size_t i = 0; i < vectorSize; i++)
            {
                if (array[i] != other.array[i])
                {
                    return false;
                }
            }

            return true;
        }

        bool operator!=(const vector<T> &other) const
        {
            if (vectorSize != other.vectorSize)
            {
                return true;
            }

            for (size_t i = 0; i < vectorSize; i++)
            {
                if (array[i] != other.array[i])
                {
                    return true;
                }
            }

            return false;
        }

        T& operator[](size_t index)
        {
            return *(array + index);
        }

        const T& operator[](size_t index) const
        {
            return *(array + index); 
        }

        T at(size_t index) const
        {
            return *(array + index);
        }


        size_t size() const
        {
            return vectorSize;
        }

        size_t maxSize() const
        {
            return reservedSize;
        }

    public:

        class Iterator
        {
        private:
            T *ptr;

        public:
            Iterator(T* ptr): ptr(ptr) {}
            
            T& operator*() const
            {
                return *ptr;
            }

            Iterator& operator++()
            {
                ++ptr;
                return *this;
            }

            Iterator operator++(int)
            {
                Iterator temp = *this;
                ++(*this);
                return temp;
            }

            Iterator& operator--()
            {
                --ptr;
                return *ptr;
            }

            Iterator operator--(int)
            {
                Iterator temp = *this;
                --(*this);
                return temp;
            }

            Iterator operator+(int n)
            {
                return Iterator(ptr + n);
            }

            Iterator operator-(int n)
            {
                return Iterator(ptr - n);
            }

            Iterator& operator+=(int n)
            {
                ptr += n;
                return *this;
            }

            Iterator& operator-=(int n)
            {
                ptr -= n;
                return *this;
            }

            int operator-(const Iterator& other) const
            {
                return ptr - other.ptr;
            }



            bool operator==(const Iterator& other) const
            {
                return ptr == other.ptr;
            }

            bool operator!=(const Iterator& other) const
            {
                return ptr != other.ptr;
            }

            bool operator<(const Iterator& other) const
            {
                return ptr < other.ptr;
            }

            bool operator>(const Iterator& other) const
            {
                return ptr > other.ptr;
            }

            bool operator<=(const Iterator& other) const
            {
                return ptr <= other.ptr;
            }

            bool operator>=(const Iterator& other) const
            {
                return ptr >= other.ptr;
            }
        };


        Iterator begin() 
        {
            return Iterator(array);
        }

        Iterator end()
        {
            return Iterator(array+vectorSize);
        }
    }; 
}


