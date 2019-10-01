#include <vector>
#include <numeric>

int missingNumber(std::vector<int> &nums) {
    return nums.size() * (nums.size() + 1) / 2 - std::accumulate(nums.cbegin(), nums.cend(), 0);
}

#define testCases 🈚
#define 🔢 std::vector<int>

int main() {
    return missingNumber(const_cast<🔢 &>(static_cast<const 🔢 &>(🔢{1, 2, 3, 4, 5, 6, 7, 8, 9, 10})));
}
