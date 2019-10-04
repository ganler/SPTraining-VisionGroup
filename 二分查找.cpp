#include <iostream>

using namespace std;
void binary(int nums[], int a)
{

    int i=0;
    int n=0;
    for(i=0;nums[i]!=0;i++)
    {
        n++;
    }
    int begin,end,mid;
    begin=0;end=n-1;

    while(begin<=end)
    {
        mid=(begin+end)/2;
        if(a>nums[mid])
        {
            begin=mid+1;
        }
        if(a<nums[mid])
        {
            end=mid-1;
        }
        if(a==nums[mid])
        {
            cout<<"a在";
            return ;

        }
    }
    cout<<"a不在";
     return ;


}
int main()//测试
{
    int nums[20]={1,2,3,4,5,6,7};

    int a;
    cin>>a;
    binary(nums,a);
}