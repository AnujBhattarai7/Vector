#pragma once

#include "Vector.h"

template<typename _T, int _TS>
inline Vector<_T>& Vector<_T, _TS>::operator=(const std::initializer_list<_T>& _D)
{

    if (Size() < _D.size())
        _Alloc(_D.size());

    int _i = 0;
    for (auto& i : _D)
    {
        _V[_i] = i;

        _i++;
    }

    _OS = _i;

    return *this;
}
