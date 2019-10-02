class Solution {    
public:
    void rotate(vector<int>& nums, int k) {
       k = k % nums.size();
        reverse(nums.begin(), nums.begin() + nums.size() - k);
        reverse(nums.begin() + nums.size() - k, nums.end());
        reverse(nums.begin(), nums.end());
    }
};

/*class Solution{   //一次移动一整个数组，然后循环k次，能出结果，但是这个方法超时了
    public:
    void rotate(vector<int>& nums, int k)
    {
        int length = nums.size();
        for(int i=0;i<k % length;i++)
        {
            int t = nums[length - 1];
            for(int j = length - 1; j > 0; j--)
            {
                nums[j] = nums[j-1];
            }
            nums[0] = t;
        }
    }
};*/
