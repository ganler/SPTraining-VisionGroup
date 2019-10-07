#include"iostream"
#include "math.h"
#include"stdio.h"
#include"time.h"
#include"stdlib.h"
#include"iomanip"
#include"string.h"
#include"vector"
using namespace std;

class Solution {
public:
    int missingnumber(vector<int>& nums) {
		int l=nums.size();
		int x;
		int s(0);
		x=l*(l+1)/2;
		for(int i=0;i<l;i++){
			s+=nums[i];
		}
		return x-s;
	}
};

void main()
{
	Solution sol;
	int a[9]={1,5,4,2,6,0,3,9,7};
	vector <int>b(a,a+9);
	cout<<sol.missingnumber(b);
	system("pause");
 }
