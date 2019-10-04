class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        vector<int>::iterator ite;
        int len=nums.size();
        int cnt=k%len;
        ite= nums.end()-cnt;
        std::reverse(nums.begin(),ite);
        std::reverse(ite,nums.end());
        std::reverse(nums.begin(),nums.end());  
    }
};
