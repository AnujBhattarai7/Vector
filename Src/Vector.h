#pragma once

#define __PRINT__(x) {std::cout << "[VECTOR]: " << x << "\n";}

#include <initializer_list>

template<typename T>
class Vector
{
private:
public:
    Vector(const std::initializer_list<T>& _V){
        __PRINT__("Array")
    }

    ~Vector() {}

    void Set() { "asdas";}  
};
