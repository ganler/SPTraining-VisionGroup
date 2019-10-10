#pragma once
#include <iostream>
#include <vector>
using namespace std;

class CSolution
{
public:
	//CSolution(void);
	//~CSolution(void);
void rotate(vector<int>& nums, int k) {
        k =  k % nums.size();
        
        int t1 = 0, t2 = 0;
        int tr;
        for (t1 = 0, t2 = nums.size() - k - 1; t1 <= t2;++t1, --t2){
            tr = nums[t1];
            nums[t1] = nums[t2];
            nums[t2] = tr;
        }
        
        for (t1 = nums.size() - k, t2 = nums.size() - 1; t1 <= t2;++t1, --t2){
            tr = nums[t1];
            nums[t1] = nums[t2];
            nums[t2] = tr;
        }
        
        for (t1 = 0, t2 = nums.size() - 1; t1 <= t2;++t1, --t2){
            tr = nums[t1];
            nums[t1] = nums[t2];
            nums[t2] = tr;
        }
    }

};

