#include <iostream>
#include "Vector.h"

int main(){
   Vector<int> _V{1, 2};
   __PRINT__(_V.Flush())
   __PRINT__(_V.Size())
   __PRINT__(_V._Capacity())
}