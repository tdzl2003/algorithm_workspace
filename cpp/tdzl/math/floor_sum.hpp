#pragma once
#include "./common.hpp"

// Source: https://github.com/atcoder/ac-library/blob/master/atcoder/math.hpp

// @param n `n < 2^32`
// @param m `1 <= m < 2^32`
// @return sum_{i=0}^{n-1} floor((ai + b) / m) (mod 2^64)

namespace internal {
    unsigned long long floor_sum_unsigned(unsigned long long n,
        unsigned long long m,
        unsigned long long a,
        unsigned long long b) {
        unsigned long long ans = 0;
        while (true) {
            if (a >= m) {
                ans += n * (n - 1) / 2 * (a / m);
                a %= m;
            }
            if (b >= m) {
                ans += n * (b / m);
                b %= m;
            }

            unsigned long long y_max = a * n + b;
            if (y_max < m) break;
            // y_max < m * (n + 1)
            // floor(y_max / m) <= n
            n = (unsigned long long)(y_max / m);
            b = (unsigned long long)(y_max % m);
            std::swap(m, a);
        }
        return ans;
    }
}

long long floor_sum(long long n, long long m, long long a, long long b) {
    assert(0 <= n && n < (1LL << 32));
    assert(1 <= m && m < (1LL << 32));
    unsigned long long ans = 0;
    if (a < 0) {
        unsigned long long a2 = safe_mod(a, m);
        ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / m);
        a = a2;
    }
    if (b < 0) {
        unsigned long long b2 = safe_mod(b, m);
        ans -= 1ULL * n * ((b2 - b) / m);
        b = b2;
    }
    return ans + internal::floor_sum_unsigned(n, m, a, b);
}

