#pragma once
#include <assert.h>
#include <vector>
#include <algorithm>

#include <ranges>

// 无向无权不可修改图
class nd_constant_graph
{
private:
    bool _builded;
    int _n;
    std::vector<pair<int, int>> _init_edges;
    std::vector<int> _out_edges;
    std::vector<int> _in_indexes;

public:
    nd_constant_graph(int n):_n(n), _builded(false), _in_indexes(n+1) {
    }

    void add_edge(int u, int v) {
        assert(!_builded);
        assert(0 <= u && u < _n);
        assert(0 <= v && v < _n);
        _init_edges.push_back({ u, v });
        _init_edges.push_back({ v, u });
    }

    void build() {
        assert(!_builded);
        _builded = true;
        std::sort(_init_edges.begin(), _init_edges.end());
        _init_edges.erase(std::unique(_init_edges.begin(), _init_edges.end()), _init_edges.end());
        _out_edges.resize(_init_edges.size());

        int j = 0;
        for (int i = 0; i < _n; i++) {
            _in_indexes[i] = j;
            while (j < _init_edges.size() && _init_edges[j].first == i) {
                _out_edges[j] = _init_edges[j].second;
                ++j;
            }
        }

        _in_indexes[_n] = _out_edges.size();
        _init_edges.clear();
    }

    // 求最远点和距离
    pair<int, int> farest_from(int start = 0);

    auto edges_from(int u) {
        assert(_builded);
        assert(0 <= u && u < _n);
        return std::ranges::subrange(_out_edges.begin() + _in_indexes[u], _out_edges.begin() + _in_indexes[u+1]);
    }

    int diameter() {
        auto [f, d0] = farest_from();
        auto [t, d1] = farest_from(f);
        return d1;
    }

    static auto make_from_edges(int n, vector<vector<int>>& edges) {
        nd_constant_graph ret(n);
        for (auto& v : edges) {
            ret.add_edge(v[0], v[1]);
        }
        ret.build();

        return ret;
    }
};
