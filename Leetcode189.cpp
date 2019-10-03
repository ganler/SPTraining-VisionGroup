class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        k%=nums.size();
        vector<int> a(nums.end()-k,nums.end());
    for (int i=nums.size()-1;i>=k;--i)
        nums[i]=nums[i-k];
    for (int i=0;i<k;++i)
        nums[i]=a[i];
    }
};
