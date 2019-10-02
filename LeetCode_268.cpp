class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int length = nums.size();
        int num1=length*(1+length)/2;
        int num2=0;
        for(int i =0;i<length;i++)
        {
            num2 = num2 + nums[i];
        }
        return num1 - num2;
    }
};
