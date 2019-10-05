// 268.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "Solution.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

int _tmain(int argc, _TCHAR* argv[])
{
	
	int a[7]={3,0,1,5,6,2,7};
	std::vector<int>nums(a,a+7);

	CSolution aaa;

	cout<<aaa.missingNumber(nums)<<endl;
	return 0;
}

