#pragma once

#include "../common.hpp"

// 无向无权图求最远点和距离

pair<int, int> farest_from(vector<vector<int>> G, int start = 0) {
    vector<int> depth(G.size(), -1);
    depth[start] = 0;
    queue<int> q;
    q.push(start);

    int last = start;

    while (q.size() > 0) {
        int v = q.front();
        last = v;
        q.pop();
        for (auto u : G[v]) {
            if (depth[u] >= 0) {
                continue;
            }
            depth[u] = depth[v] + 1;
            q.push(u);
        }
    }
    return { last, depth[last] };
}
