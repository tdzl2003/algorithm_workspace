#pragma once
#include "../common.hpp"

// 根据parent遍历树，不需要parent有序。
// parent为-1是根节点。
// 保证每个节点只调用一次，parent的调用一定早于children

template <typename F>
void tree_dp_with_parents(const vector<int>& parent, F f) {
    int n = parent.size();

    vector<int> visited(n, 0);
    stack<int> s;
    for (int i = 0; i < n; i++) {
        for (int j = i; j >= 0 && !visited[j]; j = parent[j]) {
            visited[j] = 1;
            s.push(j);
        }
        while (!s.empty()) {
            int v = s.top();
            s.pop();
            f(v);
        }
    }
}
