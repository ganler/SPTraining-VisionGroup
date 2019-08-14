#pragma once

#include <algorithm>
#include <iostream>

template <typename  Iter>
void qsort(Iter start, Iter end) 
{
    if (start >= end)
        return;
    Iter stdIter = start;
    Iter iIter = start;
    Iter jIter = end + 1;
    while (true)
    {
        while (*(++iIter) < *stdIter)
            if (iIter == end)
                break;
        while (*(--jIter)> *stdIter)
            if (jIter == start)
                break;
        if (iIter < jIter)
            std::swap(*iIter, *jIter);
        else
            break;
    }
    std::swap(*stdIter, *jIter);
    qsort(start, jIter - 1);
    qsort(jIter + 1, end);
    return;
}
