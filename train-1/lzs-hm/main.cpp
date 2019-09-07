#include "qsort.hpp"
#include <iostream>
int main()
{
    int a[] = {57, 68, 59, 52, 72, 28, 96, 33, 24};
    qsort(a,a+8);
    for(int i = 0;i<9; i++)
        std::cout<<a[i]<<std::endl;
    return 0;
}