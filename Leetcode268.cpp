class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int i=nums.size()*(nums.size()+1)/2-accumulate(nums.begin(),nums.end(),0);
        return i;
    }
};
