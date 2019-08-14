#include "qsort.hpp"

int main()
{
    int a[7] = {3,1,7,5,9,2,8};
    qsort(a, a+6);
    for (int i : a)
        std::cout << i << " ";
    std::cout << std::endl;
    return 0;
}