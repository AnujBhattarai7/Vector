#pragma once

#include <initializer_list>
#include "Iterator.h"

#define _VEC_INITIAL_SIZE_ 10
#define _VEC_CAPACITY_SIZE_MULTIPLIER_ 1.5

#define _PRINT_(x)              \
    {                           \
        std::cout << x << "\n"; \
    }

#define _VEC_ERROR_(x)      \
    {                       \
        _PRINT_(x);         \
        exit(EXIT_FAILURE); \
    }

template <typename _T, int _TS = 0>
class Vector
{
    // Comments:
    // _S : Stores Size of vector
    // _T : The class of Data

public:
    using ValueType = _T;
    using Iterator = _Iterator_Base<ValueType>;

public:
    Vector(const std::initializer_list<_T> &_D)
    {
        _Alloc(_D.size());
        *this = _D;
    }

    Vector(int Size = _TS) : _C(_TS + 2) { _Alloc(_C); }

    ~Vector()
    {
        Flush();

        ::operator delete(_V, _C * sizeof(_T));
        _V = nullptr;
    }

    // The Getters

    inline const int Size() const { return _S; }
    inline const int Capacity() const { return _C; }
    inline _T *Data() const { return &_V; }
    inline _T &at(int _i) { return _V[_i]; }

    // Copies the _O n times and assigns it
    inline void Assign(int n, const _T &_O);

    // Copies the _O from start(s) index to end(e) index
    inline void Assign(int s, int e, const _T &_O);

    inline _T &operator[](int i) { return _Get(i); }
    inline const _T &operator[](int i) const { return _Get(i); }

    inline Vector<_T> &operator=(const std::initializer_list<_T> &_D);

    // Flushes all elements of the array _V
    void Flush();

    _T &begin() const { return *_V; }
    _T &end() const { return *_V + Size(); }

    // Push_Backes the object to the end of _V by copying
    void Push_Back(const _T &O);

    // Push_Backes the object to the end of _V by moving
    void Push_Back(_T &&O);

    // Rather than moving creates adds to _V from given args...
    template <typename... Args>
    _T &Emplace_Back(Args &&...args);

    // Pops the last object in _V
    void Pop_Back();

    // Removes the given index from _V
    void Erase(int i);

    // Removes the given index from s to e in _V
    void Erase(int s, int e);

    // Reserves the given no of size in _V
    void Reserve(int Size) { _Alloc(Size); }

    Iterator begin() { return Iterator(_V); }
    Iterator end() { return Iterator(_V + _S); }

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
    int _AuthObj(_T &O) const;

    // Gets the object of the index and also checks for the object
    _T &_Get(int i);

    // Copies the data of _V into _A
    void _Copy(_T *_A);

    // Gives a error if _S <= 0
    void _AuthSize() const;

    // Allocates memory even if _C is 0
    void _Force_Alloc(int S);
};

template <typename _T, int _TS>
inline void Vector<_T, _TS>::Assign(int n, const _T &_O)
{
    Flush();

    if (n > _C)
        _Alloc(n * _VEC_CAPACITY_SIZE_MULTIPLIER_);

    for (_S = 0; _S < n; _S++)
    {
        _V[_S] = std::move(_O);
    }
}

template <typename _T, int _TS>
inline void Vector<_T, _TS>::Assign(int s, int e, const _T &_O)
{
    Erase(s, e);

    for (int i = s; i < e; i++)
    {
        _V[i] = std::move(_O);
    }
}

template <typename _T, int _TS>
inline Vector<_T> &Vector<_T, _TS>::operator=(const std::initializer_list<_T> &_D)
{
    if (_D.size() > _C)
        _Alloc(_D.size());

    int _i = 0;
    for (auto &i : _D)
    {
        _V[_i] = std::move(i);
        _i++;
    }

    _S = _i;

    return *this;
}

template <typename _T, int _TS>
inline void Vector<_T, _TS>::Flush()
{
    while (_S > 0)
    {
        _V[_S - 1].~_T();
        _S--;
    }
}

template <typename _T, int _TS>
inline void Vector<_T, _TS>::Push_Back(const _T &O)
{
    if (_S > _C)
        _Alloc(_C * _VEC_CAPACITY_SIZE_MULTIPLIER_);

    _V[_S++] = std::move(O);
}

template <typename _T, int _TS>
inline void Vector<_T, _TS>::Push_Back(_T &&O)
{
    if (_S > _C)
        _Alloc(_C * _VEC_CAPACITY_SIZE_MULTIPLIER_);

    _V[_S++] = std::move(O);
}

template <typename _T, int _TS>
inline void Vector<_T, _TS>::Pop_Back()
{
    Erase(_S - 1);
}

template <typename _T, int _TS>
inline void Vector<_T, _TS>::Erase(int i)
{
    _AuthIndex(i);

    _V[i].~_T();
    _S--;
}

template <typename _T, int _TS>
inline void Vector<_T, _TS>::Erase(int s, int e)
{
    _AuthIndex(s);
    _AuthIndex(e);

    for (int i = s; i < e; i++)
        Erase(i);
}

template <typename _T, int _TS>
inline void Vector<_T, _TS>::_Alloc(int _NS)
{
    if (_NS == 0)
        return;

    if (_V != nullptr)
    {
        int _OC = _C;
        _C = _NS;
        _T *_New = (_T *)::operator new(_C * sizeof(_T));

        _Copy(_New);

        for (int i = 0; i < _S; i++)
            _V[i].~_T();

        ::operator delete(_V, _OC * sizeof(_T));
        _V = _New;

        return;
    }

    _C = _NS;
    _V = (_T *)::operator new(_C * sizeof(_T));
    _S = 0;
}

template <typename _T, int _TS>
inline bool Vector<_T, _TS>::_AuthIndex(int I) const
{
    _AuthSize();

    if (I >= _S)
    {
        _PRINT_("[VECTOR]: Index: " << I << " out of range!!");
        exit(EXIT_FAILURE);
    }

    return true;
}

template <typename _T, int _TS>
inline _T &Vector<_T, _TS>::_Get(int i)
{
    _AuthIndex(i);
    return _V[i];
}

template <typename _T, int _TS>
inline void Vector<_T, _TS>::_Copy(_T *_A)
{
    _AuthSize();

    // Copies the data into _A
    for (int i = 0; i < _S; i++)
    {
        _A[i] = std::move(_V[i]);
    }
}

template <typename _T, int _TS>
inline void Vector<_T, _TS>::_AuthSize() const
{
    if (_S <= 0)
    {
        _PRINT_("[VECTOR]: Size is 0");
        exit(EXIT_FAILURE);
    }
}

template <typename _T, int _TS>
template <typename... Args>
inline _T &Vector<_T, _TS>::Emplace_Back(Args &&...args)
{
    if (_S > _C)
        _Alloc(_C * _VEC_CAPACITY_SIZE_MULTIPLIER_);

    new (&_V[_S]) _T(std::forward<Args>(args)...);
    return _V[_S++];
}
