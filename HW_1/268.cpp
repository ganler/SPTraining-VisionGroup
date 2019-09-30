class Solution {
public:
    int missingNumber(vector<int>& nums) {
        int length=nums.size();
        vector<int> temp(length+1);
        for(int i=0;i<length;++i){
            temp[nums[i]]=1;
        }
        for(int i=0;i<length+1;++i){
            if(temp[i]!=1)
                return i;
        }
        return 0;
    }
};
