#include <iostream>
#include <vector>
#include "Vector.h"

struct Test
{
    Test(int n = 1) : _n(n)
    {
    }

    Test(const Test &Other)
        : _n(Other._n)
    {
        _PRINT_("[TEST]: Copy");
    }

    Test(Test &&_T)
        : _n(_T._n)
    {
        _PRINT_("[TEST]: Move");
    }

    ~Test()
    {
        _PRINT_("[TEST]: Delete")
    }

    friend std::ostream &operator<<(std::ostream &os, Test &_T)
    {
        os << _T._n;
        return os;
    }

    inline Test &operator=(int n)
    {
        _n = n;
        return *this;
    }

    inline Test &operator=(const Test &_O)
    {
        _PRINT_("[TEST]: Copy");
        _n = _O.Get();
        return *this;
    }

    inline Test &operator=(Test &&_O)
    {
        _PRINT_("[TEST]: Move");
        _n = _O._n;
        return *this;
    }

    inline const int Get() const { return _n; }

    int _n = 0;
};

struct MemoryManager
{
    int _Allocation, _Free;
};

static MemoryManager _MemoryManager;

void *operator new(size_t size)
{
    std::cout << "Allocation"
              << "\n";
    _MemoryManager._Allocation += size;
    return malloc(size);
}

void operator delete(void *p, size_t size)
{
    std::cout << "Delete"
              << "\n";
    _MemoryManager._Free += size;

    free(p);
}

static void PrintMemoryMetrics()
{
    _PRINT_("[MEMORY_METRICS]: Allocated: " << _MemoryManager._Allocation << " bytes..")
    _PRINT_("[MEMORY_METRICS]: Freed: " << _MemoryManager._Free << " bytes..")
}

int main(int argc, char const *argv[])
{
    std::cout << "Hello"
              << "\n";

    {
        Vector<Test> _V;
        _V.Push_Back(Test(100));

        _PRINT_("");
        for (auto &i : _V)
            _PRINT_(i)
        _PRINT_("");
    }
    _PRINT_("");

    std::cin.get();
    PrintMemoryMetrics();

    return 0;
}
