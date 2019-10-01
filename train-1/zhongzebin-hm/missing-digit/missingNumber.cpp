class Solution {
public:
    int missingNumber(vector<int>& nums) {
        array<bool,nums.size()+1> a;
        a.fill(false);
        for(int i=0;i<nums.size();i++)
        {
            a[nums[i]]=true;
        }
        int find=0;
        while(a[find])
        {
            find++;
        }
        return find;
    }
};
