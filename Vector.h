#pragma once

#include <initializer_list>
#include <iterator>

#define _VEC_INITIAL_SIZE_ 10
#define _VEC_CAPACITY_SIZE_MULTIPLIER_ 1.5

#define _PRINT_(x)              \
    {                           \
        std::cout << x << "\n"; \
    }

template <typename _T, int _TS = 0>
class Vector
{
    // Comments:
    // _S : Stores Size of vector
    // _T : The class of Data

public:
    Vector(const std::initializer_list<_T>& _D) 
    {
        _Alloc(_D.size());
        *this = _D;
    }

    Vector(int Size = _TS) { _Alloc(Size); }

    ~Vector() { Flush(); }

    // The Getters

    inline const int Size() const { return _S; }
    inline const int Capacity() const { return _C; }
    inline _T* Data() const { return &_V; }

    inline _T& operator[](int i) { return _Get(i); }
    inline const _T &operator[](int i) const { return _Get(i); }
    
    inline Vector<_T>& operator=(const std::initializer_list<_T>& _D);

    // Finds the index of given object
    inline const int Find(const _T& _D) const;

    // Flushes all elements of the array _V
    void Flush();

    _T& begin() const { return *_V; }
    _T& end() const { return *_V + Size(); }

    // Pushes the object to the end of _V
    void Push(const _T& O);

    // Pops the last object in _V 
    void Pop();

    // Removes the given index from _V
    void Erase(int i);

private:
    // The dynamic array which stores the data
    _T *_V = nullptr;

    // The total Capacity of the _V
    int _C = 0;

    // The Size of the _V
    int _S = 0;

    // The Index where the next object will be put
    // Or the index pointing to an empty pos
    int _EmptyIndex = 0;

    // Allocates Memory in the _V
    void _Alloc(int _NS);

    // Checks if the given index is out of range or not
    bool _AuthIndex(int I) const;

    // Checks if the given object is in the _V or not
    bool _AuthObj(const _T &O);

    // Gets the object of the index and also checks for the object
    _T &_Get(int i) const;
};
