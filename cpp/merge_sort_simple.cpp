#include <vector>

#include <assert.h>

#include <iostream>

#include <algorithm>

#include <cstdlib>
#include <cmath>

std::ostream &
operator<<(std::ostream &lhs, std::vector<int> const &vec) {
    for (auto d : vec)
        lhs << d << " ";

    lhs << std::endl;

    return lhs;
}

std::vector<int> merge_sort(std::vector<int> &input) {
    if (input.size() <= 1) {
         return input;
    } else {
        /* Merge the two sorted sub-vectors */
        std::vector<int> v1(input.begin(), input.begin() + static_cast<int>(floor((input.size() + 1) / 2.0)));
        std::vector<int> v2(input.begin() + static_cast<int>(ceil(input.size() / 2.0)), input.end());

        v1 = merge_sort(v1);
        v2 = merge_sort(v2);

        /* Iterate through both, taking a value if it is greater
         * than the other */
        std::vector<int>::iterator it1 = v1.begin();
        std::vector<int>::iterator it2 = v2.begin();

        std::vector<int> result;
        for (; it1 != v1.end() && it2 != v2.end();) {
            if (*it1 <= *it2) {
                result.push_back(*it1++);
            } else {
                result.push_back(*it2++);
            }
        }

        while (it1 != v1.end())
            result.push_back(*it1++);

        while (it2 != v2.end())
            result.push_back(*it2++);

        return result;
    }
}

std::vector<int> quicksort(std::vector<int> const &input) {
    if (input.size() <= 1)
        return input;

    auto pivot = input.end() - 1;

    std::vector<int> left;
    std::vector<int> right;

    for (auto it = input.begin(); it != pivot; ++it) {
        if (*it < *pivot) {
            left.push_back(*it);
        } else {
            right.push_back(*it);
        }
    }

    std::vector<int> result;

    left = quicksort(left);
    right = quicksort(right);

    std::copy(left.begin(), left.end(), std::back_inserter(result));
    result.push_back(*pivot);
    std::copy(right.begin(), right.end(), std::back_inserter(result));

    return result;
}


int main() {
    std::vector<int> data;
    for (size_t i = 0; i < 20; ++i)
        data.push_back(rand() % 100);

    std::cout << data;

    std::cout << "Merge sort" << std::endl;
    std::cout << merge_sort(data);

    std::cout << "Quick sort" << std::endl;
    std::cout << quicksort(data);
}
