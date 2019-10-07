#include <iostream>
#include <vector>
template <typename Iter, typename T>
bool binary_search(Iter beg, Iter end, T &&val)
{
    Iter middle;

    while (beg <end)
    {
        middle =beg+(end-beg)/ 2;
        if (val == *middle)
            return true;
        else if (val > *middle)
            beg = middle + 1;
        else if (val < *middle)
            end = middle;
    }
    return false;
}
    int main()
    {

        std::vector<int> vec(10);
        int i;
        bool b1;
        for (i = 0; i < vec.size(); i++)
        {
            vec[i] = i;
            std::cout << vec[i] << "  ";
        }
      
   b1=binary_search(vec.begin(),vec.end(),10);
        if(b1)
        std::cout<<"Found it!"<<'\n';
        else
       std::cout<<"Not extis"<<'\n';
    

        return 0;
    }
