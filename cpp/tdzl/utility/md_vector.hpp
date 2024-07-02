#pragma once
#include "../common.hpp"
#include <array>
#include <vector>
#include <assert.h>

// 多维动态大小数组，可以用于DP等场景。
template <typename T, size_t dimensions>
class md_vector;

namespace internal {
    template <size_t dimensions>
    size_t md_size(const array<size_t, dimensions>& dsize) {
        size_t base = 1;
        for (int i = 0; i < dimensions; i++) {
            base *= dsize[i];
        }
        return base;
    }

    template <typename T, size_t dimensions, size_t idx_dimensions>
    class md_vector_index {
    public:
        md_vector_index(md_vector<T, dimensions>& vec, size_t base = 0): vector_(vec), base_(base) {
        }

        auto operator[] (size_t v)const {
            assert(v < vector_.dsize_[idx_dimensions - 1]);
            return md_vector_index<T, dimensions, idx_dimensions + 1>(vector_, (base_+v)*vector_.dsize_[idx_dimensions]);
        }

    private:
        md_vector<T, dimensions>& vector_;
        const size_t base_;
    };

    template <typename T, size_t dimensions>
    class md_vector_index<T, dimensions, dimensions> {
    public:
        md_vector_index(md_vector<T, dimensions>& vec, size_t base = 0) : vector_(vec), base_(base) {
        }

        T& operator[] (size_t v) const {
            return vector_.data_[base_ + v];
        }

        md_vector<T, dimensions>& vector_;
        const size_t base_;
    };

    template <typename T, size_t dimensions, size_t idx_dimensions>
    class const_md_vector_index {
    public:
        const_md_vector_index(const md_vector<T, dimensions>& vec, size_t base = 0) : vector_(vec), base_(base) {
        }

        auto operator[] (size_t v)const {
            assert(v < vector_.dsize_[idx_dimensions - 1]);
            return const_md_vector_index<T, dimensions, idx_dimensions + 1>(vector_, (base_ + v) * vector_.dsize_[idx_dimensions]);
        }

    private:
        const md_vector<T, dimensions>& vector_;
        const size_t base_;
    };

    template <typename T, size_t dimensions>
    class const_md_vector_index<T, dimensions, dimensions> {
    public:
        const_md_vector_index(const md_vector<T, dimensions>& vec, size_t base = 0) : vector_(vec), base_(base) {
        }

        const T& operator[] (size_t v) const {
            return vector_.data_[base_ + v];
        }

        const md_vector<T, dimensions>& vector_;
        const size_t base_;
    };
}


template <typename T, size_t dimensions>
class md_vector {
public:
    md_vector() {}
    md_vector(md_vector<T, dimensions>&& other): data_(other.data_), dsize_(other.dsize_) {
    }
    md_vector(const md_vector<T, dimensions>& other) : data_(other.data_), dsize_(other.dsize_) {
    }

    md_vector(array<size_t, dimensions> dsize, T default_value = T())
        : dsize_(dsize), data_(internal::md_size(dsize), default_value)
    {
    }

    md_vector& operator=(md_vector<T, dimensions>&& other) {
        data_ = other.data_;
        dsize_ = other.dsize_;
        return *this;
    }
    md_vector& operator=(const md_vector<T, dimensions>& other) {
        data_ = other.data_;
        dsize_ = other.dsize_;
        return *this;
    }

    auto operator [](size_t v) {
        return internal::md_vector_index<T, dimensions, 1>(*this)[v];
    }

    auto operator [](size_t v) const {
        return internal::const_md_vector_index<T, dimensions, 1>(*this)[v];
    }

    T& operator [](array<size_t, dimensions> idx) {
        size_t base = 0;
        for (int i = 0; i < dimensions; i++) {
            base *= dsize_[i];
            base += idx[i];
        }
        return data_[base];
    }

    vector<T> data_;
    array<size_t, dimensions> dsize_;
};


template <typename T, size_t dimensions>
istream& operator >>(istream& in, md_vector<T, dimensions>& vec) {
    return in >> vec.data_;
}

template <typename T, size_t dimensions>
void make_md_presum(md_vector<T, dimensions>& vec) {
    size_t diff = 1, base= 0;
    for (int currD = dimensions - 1; currD >= 0; currD--) {
        base = diff * vec.dsize_[currD];
        for (size_t i = 0; i+diff < vec.data_.size(); i++) {
            if (i % base + diff < base) {
                vec.data_[i + diff] += vec.data_[i];
            }
        }
        diff = base;
    }
}
