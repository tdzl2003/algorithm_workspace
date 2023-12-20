#pragma once
// 常用二进制相关
// copy from https://github.com/atcoder/ac-library/blob/master/atcoder/internal_bit.hpp

// @param n `0 <= n`
// @return 返回满足`n<=(1<<x)` 的最小的x；返回大于等于n的最小的2的幂
int ceil_pow2(int n) {
    int x = 0;
    while ((1U << x) < (unsigned int)(n)) x++;
    return x;
}

int ceil_pow2(long long n) {
    int x = 0;
    while ((1ULL << x) < (unsigned long long)(n)) x++;
    return x;
}

// @param n `1 <= n`
// @return 返回满足`(n & (1 << x)) != 0`的最小的x。返回x最低一个二进制位的下标
constexpr int lower_bit_constexpr(unsigned int n) {
    int x = 0;
    while (!(n & (1 << x))) x++;
    return x;
}

// @param n `1 <= n`
// @return 返回满足`(n & (1 << x)) != 0`的最小的x。返回x最低一个二进制位的下标
int lower_bit(unsigned int n) {
#ifdef _MSC_VER
    unsigned long index;
    _BitScanForward(&index, n);
    return index;
#else
    return __builtin_ctz(n);
#endif
}

