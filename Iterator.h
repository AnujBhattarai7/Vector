#pragma once

template <typename _ValueType>
class _Iterator_Base
{
public:
    using ValueType = _ValueType;
    using PointerType = ValueType *;
    using ReferenceType = ValueType &;

public:
    _Iterator_Base(PointerType P)
        : _P(P) {}

    _Iterator_Base &operator++()
    {
        _P++;
        return *this;
    }

    _Iterator_Base operator++(int)
    {
        _Iterator_Base it = *this;
        ++(*this);
        return it;
    }

    _Iterator_Base &operator--()
    {
        _P--;
        return *this;
    }

    _Iterator_Base operator--(int)
    {
        _Iterator_Base it = *this;
        --(*this);
        return it;
    }

    ReferenceType operator[](int i) { return *(_P + i); }
    PointerType operator->() { return _P; }
    ReferenceType operator*() { return *_P; }

    bool operator==(const _Iterator_Base &_O) const { return _P == _O._P; }
    bool operator!=(const _Iterator_Base &_O) const { return !(*this == _O); }

private:
    PointerType _P;
};

