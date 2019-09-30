class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int> temp(nums);
        int length=nums.size(),steps=k%length;
        for(int i=0;i<length;++i){
            nums[(i+steps)%length]=temp[i];
        }
    }
};
