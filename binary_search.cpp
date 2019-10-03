#include <iostream>
#include <vector>
using namespace std;

template<typename Iter,typename T>
    bool binary_search(Iter beg,Iter end,T&& val)//升序
{
    while (beg<=end)
    {
        Iter mid=beg+(end-beg)/2;
        if (val==*mid)
            return 1;
        else if (val<*mid)
            end=mid-1;
        else
            beg=mid+1;
    }
    return 0;
}

