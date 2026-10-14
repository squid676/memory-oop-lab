#pragma once
#include <cstddef>
#include <utility>

namespace forge {
template<class T> void insertion_sort(T* data, std::size_t n) {
    for (std::size_t i = 1; i < n; ++i) {
        T value = std::move(data[i]); std::size_t j = i;
        while (j > 0 && value < data[j - 1]) { data[j] = std::move(data[j - 1]); --j; }
        data[j] = std::move(value);
    }
}
template<class T> int binary_search(const T* data, std::size_t n, const T& key) {
    std::size_t lo = 0, hi = n;
    while (lo < hi) { auto mid = lo + (hi - lo) / 2; if (data[mid] < key) lo = mid + 1; else hi = mid; }
    return lo < n && !(key < data[lo]) ? static_cast<int>(lo) : -1;
}
inline unsigned long long factorial(unsigned n) { return n < 2 ? 1ULL : n * factorial(n - 1); }
}
