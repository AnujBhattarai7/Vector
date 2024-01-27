#pragma once

#include <initializer_list>
#include <iterator>

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
    Vector(const std::initializer_list<_T>& _D) 
    {
        _Alloc(_D.size());
        *this = _D;
    }

    Vector() { _Alloc(_TS); }

    ~Vector() { Flush(); }

    // The Getters

    inline const int Size() const { return _OS; }
    inline const int MaxSize() const { return _S; }
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

    // The occupied size in _V
    int _OS = 0;

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

template<typename _T, int _TS>
inline const int Vector<_T, _TS>::Find(const _T& _D) const
{
    if (_OS <= 0)
        return -1;

    for (int i = 0; i < Size(); i++)
    {
        if (_D == _V[i])
            return i;
    }

    return -1;
}

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
    _OS = 0;
}

template<typename _T, int _TS>
inline void Vector<_T, _TS>::Push(const _T& O)
{
    if (_OS == _S)
        _Alloc(_C);

    _V[_OS++] = O;
}

template<typename _T, int _TS>
inline void Vector<_T, _TS>::Pop()
{
    Erase(Size() - 1);
}

template<typename _T, int _TS>
inline void Vector<_T, _TS>::Erase(int i)
{
    _EmptyIndex = i;

}

template <typename _T, int _TS>
inline void Vector<_T, _TS>::_Alloc(int _NS)
{
    // Copy the data and re-enter it
    if (_V != nullptr)
    {
        // For better performace use std::move
        // Copies and saves the data
        
        _T temp[Size()];

        for (int i = 0; i < Size(); i++)
        {
            // For better performace use std::move
            temp[i] = _V[i];
        }

        delete[] _V;

        // Putting the data back to the _V
        _V = new _T[_NS];
        bool _Run = true;
        int i = 0;

        while (_Run && i <= _NS)
        {
            _V[i] = temp[i];
            i++;

            if (i > Size() - 1)
                _Run = false;
        }

        // Update the data
        _OS = i;
        _S = _NS;
        _C = _S * _VEC_CAPACITY_SIZE_MULTIPLIER_;

        return;
    }

    // For Empty _V only need to Alloc the _V
    _V = new _T[_NS];
    _S = _NS;
    _C = _S * _VEC_CAPACITY_SIZE_MULTIPLIER_;
}

template <typename _T, int _TS>
inline bool Vector<_T, _TS>::_AuthIndex(int I) const
{
    if (_OS <= 0)
        return false;

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
    if (Find(O) != -1)
        return true;
    return false;
}

template <typename _T, int _TS>
inline _T &Vector<_T, _TS>::_Get(int i) const
{
    _AuthIndex(i);
    return _V[i];
}

#include "Operators.h"
