#pragma once

#include <vector>
#include <tuple>

/*
op需要满足多个条件：
- 结合律，op(a,op(b,c)) = op((a,b), c)，简写为 op(a,b,c)
- 单调性，op(a, b) <= b 或者 op(a,b) >= b
- 复杂度良好，{op(a),op(a,b},op(a,b,c).....} 中只有较少（一般低于lgU) 个不同的元素
常用的符合条件的op： and/or/gcd

f(l0, l1, r, v):  对任何的l0<=i<l1，有op(a[i]..a[r-1]) = v
*/
template <typename S, S (*op)(S,S), typename F>
void logtrick(const vector<S>& arr, F f) {
    std::vector<std::tuple<size_t, size_t, S>> dp;

    for (size_t i = 0; i < arr.size(); i++) {
        auto curr = arr[i];
        for (auto& v : dp) {
            get<2>(v) = op(get<2>(v), curr);
        }
        dp.push_back(make_tuple(i, i + 1, curr));

        size_t k = 0;
        for (size_t j = 1; j < dp.size(); j++) {
            if (get<2>(dp[k]) != get<2>(dp[j])) {
                dp[++k] = dp[j];
            }
            else {
                get<1>(dp[k]) = get<1>(dp[j]);
            }
        }
        dp.resize(k+1);
        for (auto v : dp) {
            f(get<0>(v), get<1>(v), i+1, get<2>(v));
        }
    }
}
