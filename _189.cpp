class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(k>=nums.size())
            k=k%nums.size();
        vector<int> a(nums.size());
        int i;
        for(i=0;i<k;i++)
            a[i]=nums[nums.size()-k+i];
        for(i=k;i<nums.size();i++)
            a[i]=nums[i-k];
        for(i=0;i<nums.size();i++)
            nums[i]=a[i];      
    }
};
