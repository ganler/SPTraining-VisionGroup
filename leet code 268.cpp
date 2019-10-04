#include <iostream>

class Solution {
public:
    int missingNumber(vector<int>& nums)
    {
        for (int i = 0; i < nums.size(); i++)
        {
            for (int j = i + 1; j < nums.size(); j++)
            {
                if (nums[i] > nums[j])
                {
                    int temp = nums[i];
                    nums[i] = nums[j];
                    nums[j] = temp;
                }
            }
        }
        int i=0;
        int n=0,sum=0;
        int s;
        for(i=0;nums[i]!=0;i++)
        {
            n++;
            sum=sum+nums[i];
        }
        s=(n+1)/2*(nums[0]+nums[n-1]);
        return s-sum;

    }
};