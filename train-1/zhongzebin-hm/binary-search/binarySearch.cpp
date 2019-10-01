template<typename Iter,typename T>
bool binary_search(Iter beg,Iter end,T&& val)
{
    if(*beg==val || *end==val)
        return true;
    if(*beg==*end)
        return false;
    Iter med=(end-beg)/2+beg;
    if(*med==val)
        return true;
    else
        if(*med>val)
            binary_search(beg,med,val);
        else
            binary_search(med,end,val);
}
