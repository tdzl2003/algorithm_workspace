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

struct tree_graph
{
    tree_graph(int n_ = 0): n(n_), edge_end_index(n) {

    }
    void add_edge(int u, int v) {
        edges.push_back({ u, v });
        edges.push_back({ v, u });
    }
    void build() {
        assert(edges.size() == 2 * n - 2);
        sort(edges.begin(), edges.end());
        for (int i = 0; i < n; i++) {
            if (i) {
                edge_end_index[i] = edge_end_index[i - 1];
            }
            while (edge_end_index[i] < edges.size() && edges[edge_end_index[i]].first == i) {
                edge_end_index[i]++;
            }
        }
    }
    auto edge_begin(int u) {
        if (u == 0) {
            return edges.begin();
        }
        return edges.begin() + edge_end_index[u - 1];
    }
    auto edge_end(int u) {
        return edges.begin() + edge_end_index[u];
    }
    template <typename F, typename G>
    void dfs(int v, const F& pre, const G& post, int parent = -1) {
        int start = v ? edge_end_index[v - 1] : 0;
        int end = edge_end_index[v];
        pre(v, parent);
        for (int i = start; i < end; i++) {
            int u = edges[i].second;
            if (u != parent) {
                dfs(u, pre, post, v);
            }
        }
        post(v, parent);
    }

    int n;
    vector<pair<int, int>> edges;
    vector<int> edge_end_index;
};
