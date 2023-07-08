#pragma once

template <typename T>
struct reduce_range_helper {
    vector<T> values;
    void prepare() {
        sort(values.begin(), values.end());
        values.erase(unique(values.begin(), values.end()), values.end());
    }

    int operator[](T v) {
        return lower_bound(values.begin(), values.end(), v) - values.begin();
    }

    void push(T i) {
        values.push_back(i);
    }

    size_t size() {
        return values.size();
    }
};
