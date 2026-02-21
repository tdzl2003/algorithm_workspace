#pragma once

#include "./common.hpp"

template <typename T, size_t N>
struct matrix {
    array<array<T, N>, N> arr{};

    matrix() = default;

    matrix(std::initializer_list<std::initializer_list<T>> init) {
        // 先清零（arr{} 已清零，但这里更语义化）
        for (int i = 0; i < N; ++i)
            for (int j = 0; j < N; ++j)
                arr[i][j] = T{};

        int i = 0;
        for (auto row : init) {
            if (i >= N) break; // 或 assert/throw
            int j = 0;
            for (auto v : row) {
                if (j >= N) break;
                arr[i][j] = v;
                ++j;
            }
            ++i;
        }

        // 如果你希望严格校验 N×N（推荐 debug 下做）
         assert((int)init.size() == N);
         for (auto row : init) assert((int)row.size() == N);
    }

    matrix& operator *=(const matrix& rhs) {
        *this = *this * rhs;
        return *this;
    }

    matrix operator*(const matrix& rhs) const {
        matrix res{};
        for (int i = 0; i < N; i++) {
            for (int k = 0; k < N; k++) {
                for (int j = 0; j < N; j++) {
                    res.arr[i][j] += arr[i][k] * rhs.arr[k][j];
                }
            }
        }
        return res;
    }

    matrix pow(long long n) const;

    array<T, N> apply(const array<T, N>& vec) const {
        array<T, N> res{};
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                res[i] += arr[i][j] * vec[j];
            }
        }
        return res;
    }
};

template<typename T, size_t N>
struct one<matrix<T, N>> {
    static matrix<T, N> make() {
        matrix<T, N> res{};
        for (size_t i = 0; i < N; ++i) res.arr[i][i] = T{ 1 };
        return res;
    }
};

template <typename T, size_t N>
matrix<T, N> matrix<T, N>::pow(long long n) const {
    return ::pow(*this, n);
}
