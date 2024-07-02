#pragma once

#include "../common.hpp"

// 无向无权图求最远点和距离

inline std::pair<int, int> nd_constant_graph::farest_from(int start) {
    std::vector<int> depth(_n, -1);
    depth[start] = 0;
    std::queue<int> q;
    q.push(start);

    int last = start;

    while (q.size() > 0) {
        int v = q.front();
        last = v;
        q.pop();
        for (auto u : edges_from(v)) {
            if (depth[u] >= 0) {
                continue;
            }
            depth[u] = depth[v] + 1;
            q.push(u);
        }
    }
    return { last, depth[last] };
}
