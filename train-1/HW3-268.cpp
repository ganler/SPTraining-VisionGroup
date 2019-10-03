class Solution {
public:
    int missingNumber(vector<int>& nums) {
        vector <int>:: iterator e;
        int i,missing_num;
        int max_num=nums.size();
        vector <int> nums_temp(max_num+1,-1);  //新建完整数组，全赋-1      
        for(e=nums.begin();e!=nums.end();e++){  
            nums_temp[*e]=*e;
        }
        for(i=0;i<=max_num;i++){           //遍历查-1
            if(nums_temp[i]==-1){
                cout<<i;
                missing_num= i;
            }
        }
        return missing_num;
    }
};
