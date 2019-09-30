template<typename Iter,typename T>
bool binary_search(Iter beg,Iter end,T&& val)
{
    while (beg<=end)
    {
        Iter mid=beg+(end-beg)/2;
        if(*mid==val)
        {
            return 1;
        }
        else if(val>*mid)
        {
            beg=mid+1;
        }
        else
        {
            end=mid-1;
        }
    }
    return 0;
}
