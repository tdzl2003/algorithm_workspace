#pragma once

template <typename C, typename W>
C knapsack_01(vector<W> choices, W target) {
    vector<C> dp(target+1);
    dp[0] = 1;
    for (auto v : choices) {
        for (int i = target; i>=v; i--) {
            dp[i] += dp[i-v];
        }
    }
    return dp[target];
}
