#pragma once
#include "../common.hpp"
#include <ranges>

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
    tree_graph(int n_ = 0): n(n_), edge_start_index(n_), edge_end_index(n_), sz(n_), mss(n_) {

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
                edge_start_index[i] = edge_end_index[i] = edge_end_index[i - 1];
            }
            while (edge_end_index[i] < edges.size() && edges[edge_end_index[i]].first == i) {
                edge_end_index[i]++;
            }
        }
    }
    auto edge_begin(int u) {
        return edges.begin() + edge_start_index[u];
    }
    auto edge_end(int u) {
        return edges.begin() + edge_end_index[u];
    }

    auto edges_from(int u) {
        return std::ranges::subrange(edge_begin(u), edge_end(u));
    }

    template <typename F, typename G>
    void dfs(int v, const F& pre, const G& post, int parent = -1) {
        int start = edge_start_index[v];
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

    vector<int> sz, mss;

    // 求重心，有两个时，任意求一个。
    int center(int v, int parent = -1) {
        int n = 0;
        dfs(v, [&](int v, int p) {
            n++; sz[v] = 0; mss[v] = 0;
            }, [&](int v, int p) {}, parent
        );
        int ret = -1;

        dfs(v, [&](int v, int p) {
                sz[v]++;
            }, [&](int v, int p) {
                if (p >= 0) {
                    sz[p] += sz[v];
                }
                mss[v] = max(mss[v], n - sz[v]);
                if (mss[v] <= n / 2) {
                    ret = v;
                }
                if (p >= 0) {
                    mss[p] = max(mss[p], sz[v]);
                }
                }, parent);

        return ret;
    }

    // 重心分治/点分治
    template <typename F, typename G>
    void decomposition(const F& pre, const G& post) {
        auto dfs1 = [&, this](auto& dfs1, int root) -> void {
                auto center = this->center(root, -1);
                pre(center);
                for (auto [_, v] : this->edges_from(center)) {
                    // 删掉到父的边
                    for (int i = edge_start_index[v]; i < edge_end_index[v]; i++) {
                        if (edges[i].second == center) {
                            swap(edges[i], edges[edge_end_index[v] - 1]);
                            edge_end_index[v]--;
                            dfs1(dfs1, v);
                            // 还原
                            edge_end_index[v]++;
                            break;
                        }
                    }
                }
                post(center);
            };

        dfs1(dfs1, 0);
    }

    int n;
    vector<pair<int, int>> edges;
    vector<int> edge_start_index;
    vector<int> edge_end_index;
};
