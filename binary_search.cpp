//
// Created by lisihang on 2019/10/1.
//

template <typename Iter, typename T>
    bool binary_search(Iter beg, Iter end, T&& val)
{
    std::sort(beg,end);
    auto mid = beg + (end - beg)/2;
    while(mid != end && *mid !=val)
    {
        if(val < *mid)
            end = mid;
        else
            beg = mid + 1;
        mid = beg+(end - beg)/2;
    }
    if(*mid == val)
        return true;
    else
        return false;
}

