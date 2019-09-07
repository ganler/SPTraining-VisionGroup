#pragma once
#include<algorithm>
template <typename Iter>
void qsort(Iter beg, Iter end)
{
    // Implementation.
    if(end<=beg) return;
    auto key=*beg,i=beg,j=end;
    while(1)
    {
        while(*i<key)
        {
            i++;
            if(i==end)  break;
        }
        while(*j>key)
        {
            j--;
            if(j==beg)  break;
        }
        if(i>=j) break;
        std::swap(*i,*j);
    }
    std::swap(key,*j);
    qsort(beg,j-1);
    qsort(j+1,end);
}