#include <iostream>
#include <vector>
#include "Vector.h"

int main(int argc, char const *argv[])
{
    std::cout << "Hello" << "\n";
    Vector<int> _V1 = { 1, 2, 3 };
    _V1.Push(100);
    _V1.Push(20);

    std::vector<int> _P;
    _P.pop_back();

    _PRINT_(_V1.Size());
    _PRINT_(_V1.MaxSize());
    _PRINT_(_V1.Capacity());
    _PRINT_("");

    for (int i = 0; i < _V1.Size(); i++)
    {
        _PRINT_(_V1[i])
    }

    std::cin.get();

    return 0;
}

