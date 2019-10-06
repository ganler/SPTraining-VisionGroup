class Solution{
public:
      void rotate(vector<int>& nums,ink k)
          {
            int num1,num2,j,count=0;
            int length=nums.size()
                k=k%length
             if(k==0)  return;
             for(int i=0;i<=k;i++)
              {
                if(count>=length)  break;
                 j=i;
                 num1=nums[i] 
                 while((j+k)%length!=i)
                  {
                    num2=nums[(j+k)%length];
                    nums[(j+k)%length]=num1;
                    j=(index+k)%length;
                    num1=num2;
                    count++;
                  } 
                  nums[i]=num1;
                  count++;
               }    
            } 
