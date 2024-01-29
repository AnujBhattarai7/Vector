#include <iostream>
#include <vector>
#include "Vector.h"

struct MemoryManager
{
    int _Allocation, _Free;
};

static MemoryManager _MemoryManager;

void* operator new(size_t size)
{
    _MemoryManager._Allocation += size;
    void* p = malloc(size);
    return p;
}

void operator delete(void* p, size_t size)
{
    _MemoryManager._Free += size;
    free(p);
}


int main(int argc, char const *argv[])
{
    std::cout << "Hello" << "\n";

    int* n = new int[2];
    delete[] n;

    std::cin.get();
    
    _PRINT_("Memory Allocated: " << _MemoryManager._Allocation << " bytes.");    
    _PRINT_("Memory Freed: " << _MemoryManager._Free << " bytes.");

    return 0;
}

