#include<iostream>
#include<iterator>
#include<vector>
using namespace std;
template<typename Iter,typename T>
   bool binary_search(Iter beg,Iter end,const T& val)
   {
	   while(1)
	   {Iter mid=beg+(end-beg)/2;
         if (val<*mid&&end!=beg)
			end=mid;
        else if(val>*mid&&end!=beg)
			beg=mid;
         else if(*mid==val)
          return true;
         else if(val!=*mid&&end==beg)
			 return false;}}