#include<iostream>
#include<vector>
#include<iterator>
using namespace std;
template<typename Iter,typename T>
bool binary_search(Iter beg,Iter end,T&& val)
{
    Iter L=beg;
    Iter H=end;
    Iter M=L;
    int d=distance(L,H);
    while(L<=H)
    {
        M=L+d/2;
        if(val==*M)
        {
            return 1;
        }
        else if(val>*M)
        {
            L=M+1;
	    d=d/2;
        }
        else
        {
            H=M-1;
	    d=d/2;
        }
    }
    return 0;
}
