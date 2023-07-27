#pragma once

template <typename T, typename Map = map<T, int>>
Map count(const vector<T>& arr) {
    Map ret;
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

template <typename T, typename Pred>
void remove_if(vector<T>& arr, Pred pred) {
    arr.erase(remove_if(arr.begin(), arr.end(), pred), arr.end());
}


