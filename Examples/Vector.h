#pragma once

#include <initializer_list>

#define _VEC_INITIAL_SIZE_ 10
#define _VEC_CAPACITY_SIZE_MULTIPLIER_ 1.5

#define _PRINT_(x)              \
    {                           \
        std::cout << x << "\n"; \
    }

template <typename _T, int _TS = _VEC_INITIAL_SIZE_>
class Vector
{
    // Comments:
    // _S : Stores Size of vector
    // _T : The class of Data

public:
    Vector(const std::initializer_list<_T> &_D) { _Alloc(_D.size()); }
    Vector() { _Alloc(_TS); }

    ~Vector() { Flush(); }

    // The Getters

    inline const int Size() const { return _S; }
    inline const int Capacity() const { return _C; }

    inline _T &operator[](int i) { return _Get(i); }

    // Flushes all elements of the array _V
    void Flush();

private:
    // The dynamic array which stores the data
    _T *_V = nullptr;

    // The total Capacity of the _V
    int _C = 0;

    // The Size of the _V
    int _S = 0;

    // Allocates Memory in the _V
    void _Alloc(int _NS);

    // Checks if the given index is out of range or not
    bool _AuthIndex(int I);

    // Checks if the given object is in the _V or not
    bool _AuthObj(const _T &O);

    // Gets the object of the index and also checks for the object
    _T &_Get(int i);
};

template <typename _T, int _TS>
inline void Vector<_T, _TS>::Flush()
{
    // Deletes the array
    if(_V != nullptr)
        delete[] _V;

    // Clears the data
    _V = nullptr;
    _S = 0;
    _C = 0;
}

template <typename _T, int _TS>
inline void Vector<_T, _TS>::_Alloc(int _NS)
{
    // Copy the data and re-enter it
    if (_V != nullptr)
    {
        // For better performace use std::move
    }

    // For Empty _V only need to Alloc the _V
    _V = new _T[_NS];
    _S = _NS;
    _C = _S * _VEC_CAPACITY_SIZE_MULTIPLIER_;
}

template <typename _T, int _TS>
inline bool Vector<_T, _TS>::_AuthIndex(int I)
{
    if (I >= Size())
    {
        _PRINT_("[VECTOR][ERROR]: Index: " << I << " out of range!!")
        exit(EXIT_FAILURE);

        return false;
    }
    return true;
}

template <typename _T, int _TS>
inline bool Vector<_T, _TS>::_AuthObj(const _T &O)
{
    for (int i = 0; i < Size(); i++)
    {
        if (_V[i] == O)
            return true;
    }

    return false;
}

template <typename _T, int _TS>
inline _T &Vector<_T, _TS>::_Get(int i)
{
    _AuthIndex(i);
    return _V[i];
}
