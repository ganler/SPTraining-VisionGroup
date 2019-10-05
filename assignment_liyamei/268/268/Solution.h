#pragma once
#include <iostream>
#include <vector>
#include <numeric>
using namespace std;

class CSolution
{
public:
	//CSolution(void);
	//~CSolution(void);
int missingNumber(vector<int>& nums) 
{
	int n=nums.size();
	int sum1=n*(n+1)/2;
	int sum2=std::accumulate(nums.begin(),nums.end(),0);
	return sum1-sum2;
}
};

