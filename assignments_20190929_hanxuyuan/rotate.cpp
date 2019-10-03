#include <iostream>
#include<vector>
#include <algorithm>
 
using namespace std;

void rotate(vector<int>& nums, int k);
void rotate_once(vector<int>& nums);

int main(){
    vector<int> nums;
    for(int i=0;i<10;i++)
    {
        nums.push_back(i);
    }
    rotate(nums, 5);
    for(int i=0;i<10;i++)
    {
        cout<<nums[i]<<",";    
    }
}
void rotate(vector<int>& nums, int k) {
    for(int i=1; i<=k; i++){
        rotate_once(nums);
    }
}
void rotate_once(vector<int>& nums){
    int temp;
    temp = nums[nums.size()-1];
    nums.pop_back();
    reverse(nums.begin(), nums.end());
    nums.push_back(temp);
    reverse(nums.begin(), nums.end());
}
