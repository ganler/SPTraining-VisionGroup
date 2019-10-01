#include <iostream>
#include <vector>

/// @return: `true` if value is in [begin, end)
/// @requirements
///   - iterator can randomly access memory
///   - the sequence should be sorted in non-descending order
template<typename Iterator, typename Value>
bool binarySearch(Iterator begin, Iterator end, Value &&value) {
    while (begin < end) {
        auto mid = begin + (end - begin) / 2;
        if (*mid == value) { return true; }
        if (*mid > value) { end = mid; }
        else { begin = mid + 1; }
    }

    return false;
}

const std::pair<std::vector<int>, int> testCases[] = {
        {{1, 4, 6, 8, 10, 199}, 8},
        {{3, 5, 66, 88, 99, 100}, 3},
        {{1, 2, 4}, 4},
        {{}, 0},
        {{1, 5, 8}, 0},
        {{0}, 0}
};

int main() {
    for (auto &&pair : testCases) {
        std::cout << binarySearch(pair.first.cbegin(), pair.first.cend(), pair.second) << std::endl;
    }
}