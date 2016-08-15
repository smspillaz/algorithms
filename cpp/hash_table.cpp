#include <map>
#include <array>
#include <iostream>

typedef std::array<std::pair<int, int>, 128> HashTable;

namespace {
    inline constexpr unsigned int HashFunction(int input) {
        return input % 128;
    }
}

int main(void) {
    HashTable ht;

    std::fill(ht.begin(), ht.end(), std::pair<int, int>(-1, -1));
    std::array<std::pair<int, int>, 5> values = {{
        { 128, 1 },
        { 2057, 2 },
        { 256, 3 },
        { 257, 4 },
        { 512, 5 }
    }};

    for (auto const &value_pair : values) {
        unsigned int hash = HashFunction(value_pair.first);
        size_t n = 128;
        while (ht[hash].first != -1 && n != 0) {
            hash = (hash + 1) % 128;
            --n;
        }

        // We have a bucket left and can insert our hash
        if (n) {
            ht[hash] = value_pair;
        }
    }

    for (auto const &value_pair : ht) {
        std::cout << value_pair.first << " " << value_pair.second << std::endl;
    }

    for (auto const &value_pair : values) {
        unsigned int hash = HashFunction(value_pair.first);
        size_t n = 128;
        while (ht[hash].first != -1 && n != 0) {
            if (ht[(hash + 1) % 128].first == -1 ||
                ht[hash].first == value_pair.first) {
                std::cout << value_pair.second << " " << hash << std::endl;
                break;
            } else {
                hash = (hash + 1) % 128;
                n--;
            }
        }
    }
}