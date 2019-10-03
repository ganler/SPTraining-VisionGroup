#include <iostream>
#include <vector>
using namespace std;
int missingNumber(vector<int>& nums);
int missingNumber(vector<int>& nums) {
	int n = nums.size();
	int sum_should_be = n*(n-1)/2;
	int sum = 0;
	int missingNumber = 0;
	for(int i=0; i<n; i++){
		sum += i;
	}
	missingNumber = n-sum+sum_should_be;
	return missingNumber;
    }
};
int main(){
	vector<int>
}
