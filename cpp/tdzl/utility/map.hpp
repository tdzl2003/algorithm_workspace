#pragma once
#include "../common.hpp"

template <typename K, typename V>
V get(const unordered_map<K, V>& map, const K& k) {
    auto itor = map.find(k);
    if (itor == map.end()) {
        return V();
    }
    return itor->second;
}

template <typename K, typename V>
V get(const map<K, V>& map, const K& k) {
    auto itor = map.find(k);
    if (itor == map.end()) {
        return V();
    }
    return itor->second;
}
