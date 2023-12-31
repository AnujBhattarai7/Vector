#pragma once

#define __PRINT__(x) {std::cout << "[VECTOR]: " << x << "\n";}

#include <initializer_list>

template<typename _T>
class Vector
{
private:
    _T* _A = nullptr; // _A = Array
    int _S = 0, _C = 0; // _S = Size of _A, _C = Total capacity of _A

public:
    Vector(const std::initializer_list<_T>& _V);
    ~Vector();

    inline int Size() {return _S;}
    inline int _Capacity() {return _C;}
    inline bool Flush() {return _Flush();}
private:
    void _Alloc(int _S); // Allocates memory in the _A
    bool _Flush(); // Flushes the Array(_A)
    void _Reset(); // Resets The basic values of Vector
};

template<typename _T>
Vector<_T>::Vector(const std::initializer_list<_T>& _V)
{
    
}

template<typename _T>
Vector<_T>::~Vector()
{
    _Flush();
}

template<typename _T>
bool Vector<_T>::_Flush()
{
    if (_A != nullptr)
    {
        delete[] _A;
        _A = nullptr;
        _Reset();
    }

    if (_A == nullptr)
        return true;

    return false;
}

template<typename _T>
void Vector<_T>::_Reset()
{
    _S = 0;
    _C = 0;
}
