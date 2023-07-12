#pragma once
#include <chrono>

template<typename T>
struct custom_hash {};

static uint64_t __splitmix64(uint64_t x) {
    static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
    x += FIXED_RANDOM;
    // http://xorshift.di.unimi.it/splitmix64.c
    x += 0x9e3779b97f4a7c15;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
    x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
    return x ^ (x >> 31);
}

template<>
struct custom_hash<uint64_t> {
    size_t operator()(uint64_t x) const {
        return __splitmix64(x);
    }
};

template<>
struct custom_hash<int64_t> {
    size_t operator()(int64_t x) const {
        return __splitmix64(x);
    }
};
