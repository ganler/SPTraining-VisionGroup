// 189.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Solution.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	int a[7]={1,2,3,4,5,6,7};
	vector<int> nums(a,a+7);

	CSolution aaa;
	
	aaa.rotate(nums,3);
	for (int i=0;i<nums.size();i++)
	{
		cout<<nums[i]<<endl;
	}
	
	return 0;
}

