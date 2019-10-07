class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int i,res=nums.size();
        for(i=0;i<nums.size();i++)
        {
            res=res^nums[i];
            res=res^i;
        }
        return res;
    }
};
