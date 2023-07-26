#pragma once

template <typename T>
map<T, int> count(const vector<T>& arr) {
    map<T, int> ret;
    for (auto& v : arr) {
        ret[v]++;
    }
    return ret;
}

template <typename T>
T max(const vector<T>& arr) {
    if (arr.size() == 0) {
        return T();
    }
    auto ret = arr[0];
    for (auto& v:arr) {
        ret = max(ret, v);
    }
    return ret;
}

template <typename T>
T min(const vector<T>& arr) {
    if (arr.size() == 0) {
        return T();
    }
    auto ret = arr[0];
    for (auto& v:arr) {
        ret = min(ret, v);
    }
    return ret;
}
