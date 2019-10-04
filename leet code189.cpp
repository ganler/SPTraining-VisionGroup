#include <iostream>
class Solution {
public:
    void rotate(vector<int>& nums, int k)
    {
        k=k%nums.size();//k>数组长度的情况
        for(int i=0;i<k;i++)
        {
            int tmp=nums[nums.size()-1];

            for(int j=nums.size()-1;j>0;j--)
            {
                nums[j]=nums[j-1];
            }
            nums[0]=tmp;
        }
        std::cout<<'[';
        for(int i=0;i<nums.size()-1;i++)
        {
            std::cout<<nums[i]<<",";
        }
        std::cout<<nums[nums.size()-1]<<"]";
    }

};

