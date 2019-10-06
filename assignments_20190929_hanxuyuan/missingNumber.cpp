#include <iostream>
#include <vector>

using namespace std;

int get_missingNumber(vector<int>& nums);

int main(){
	vector<int> nums{0,1,2,4,5};
	int missingNumber;
	missingNumber = get_missingNumber(nums);

	cout << "missingNumber is " << missingNumber << endl;
}
int get_missingNumber(vector<int>& nums) {
	int n;
	n = nums.size();
	int sum_should_be;
	sum_should_be = n*(n-1)/2;
	int sum ;
	sum = 0;
	int missingNumber;
	missingNumber = 0;
	for(int i=0; i<n; i++){
		sum += nums[i];
	}
	missingNumber = n-sum+sum_should_be;
	return missingNumber;
    };
