#include"iostream"
#include"vector"
using namespace std;

class Solution {
public:
    void rotate(vector<int>& nums, int k) {
        int len=nums.size();
		int a;
		k=k%len;
		for(int i=0;i<k;i++){
			nums.push_back(nums[i]);
		}
		for(int i=0;i<len;i++){
			nums[i]=nums[i+k];
		}
		for(int i=len;i<len+k;i++){
		nums.pop_back();
		}
	}
};

void main()
{
	Solution sol;
	//int b[5]={1,2,3,4,5};
	//vector<int> a(b,b+5);
	vector<int> a;
	for(int i=1;i<=7;i++)
		a.push_back(i);
	sol.rotate(a,3);
	for(int i=0;i<7;i++)
		cout<<a[i]<<" ";
	system("pause");
 }
