class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        if(nums.size()!=1 && nums.size()!=0 && k!=0 && k%nums.size()!=0)
        {
            vector<int> temp;
            for(int num=1;num<=k%nums.size();num++)
            {
                temp.push_back(nums[nums.size()-num]);
            }
            for(int i=nums.size()-1;i>=k%nums.size();i--)
            {
                nums[i]=nums[i-k%nums.size()];
            }
            for(int num=0;num<temp.size();num++)
            {
                nums[num]=temp[temp.size()-1-num];
            }
        }
    }
};
