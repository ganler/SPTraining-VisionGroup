class Solution:
           int missingNumber(vector<int>& nums)
             {
               int length=nums.size(),sum=0;
               int n=length(length+1)/2;
               for(int i=0;i<length;i++)              
                      sum=sum+nums[i];
                int aim=n-sum;
                  return aim;
              }
