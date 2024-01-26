#include <iostream>
#include "Vector.h"

int main(int argc, char const *argv[])
{
    std::cout << "Hello" << "\n";
    Vector<int> _V1;

    _PRINT_(_V1.Size());
    _PRINT_(_V1.Capacity());
    
    _V1.Flush();
    
    _PRINT_(_V1.Size());
    _PRINT_(_V1.Capacity());
    
    std::cin.get();

    return 0;
}

