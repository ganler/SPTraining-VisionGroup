 #include<vector>.
 #include<iostream>
 void rotate(vector<int>& nums, int k) {
        if(k>=nums.size())
            k%=nums.size();
        if(k!=0)
        {
            for(int i=k;i>0;i--)
            {
                int temp=nums[nums.size()-1];
                for(int j=nums.size()-1;j>=1;j--)
                {
                    nums[j]=nums[j-1];
                }
                nums[0]=temp;}
         
            }
       }
  int missingNumber(vector<int>& nums) {
        int m=0,n,o;
        for(int i=0;i<nums.size();i++)
        m=m+nums[i];
        o=(1+nums.size())*nums.size()/2;
        n=o-m;
        return n;
    }
