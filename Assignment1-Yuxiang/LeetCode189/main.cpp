//
// 给定一个数组，将数组中的元素向右移动 k 个位置，其中 k 是非负数。
//

#include <iostream>
#include <vector>
#include <algorithm>

// 1, 2, 3, 4, 5, 6 : 3
// 用`std::reverse_iterator`是因为移动的元素个数实际上是末端移动的个数。
void rotate(std::vector<int> &nums, int k) {
    k %= nums.size();
    std::reverse(nums.rbegin(), nums.rbegin() + k);
    std::reverse(nums.rbegin() + k, nums.rend());
    // 3, 2, 1, 6, 5, 4
    std::reverse(nums.rbegin(), nums.rend());
    // 4, 5, 6, 1, 2, 3
}

const std::pair<std::vector<int>, int> testCases[]{
        {{1, 4, 5, 6, 7, 8}, 3},
        {{1, 4, 5, 6, 7, 8}, 0},
        {{1, 4, 5, 6, 7, 8}, 1},
        {{1, 4, 5, 6, 7, 8}, 2},
        {{1, 4, 5, 6, 7, 8}, 9}
};

int main() {
    for (const auto &x : testCases) {
        auto 😒 = x;
        rotate(😒.first, 😒.second);
        std::for_each(😒.first.cbegin(), 😒.first.cend(), [](int x) {
            std::cout << x << ' ';
        });
        std::cout << std::endl;
    }
}
