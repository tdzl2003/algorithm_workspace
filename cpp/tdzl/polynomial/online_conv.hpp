#include "./convolution.hpp"

// 在线卷积，每次输入f和g的各一个数，求出到当前位置为止的卷积
// 均摊复杂度 O(Nlg^2N)
// reference: https://qiita.com/Kiri8128/items/1738d5403764a0e26b4c

template <typename mint>
struct online_conv {
    vector<mint> f, g;
    vector<mint> result;
    int idx = 0;

    void conv(int l0, int l1, int sz) {
        vector<mint> f0, g0;
        for (int i = 0; i < sz; i++) {
            f0.push_back(f[l0 + i]);
            g0.push_back(g[l1 + i]);
        }
        vector<mint> r0 = convolution(f0, g0);

        for (int i = 0; i < r0.size(); i++) {
            result[l0 + l1 + i] += r0[i];
        }
    }

    mint query(mint a, mint b) {
        f.push_back(a);
        g.push_back(b);
        result.resize(result.size() + 2);
        if (idx == 0) {
            result[0] = a * b;
            return result[idx++];
        }

        result[idx] += a * g[0] + b * f[0];
        for (int pw = 2; pw <= idx && (idx+2) % pw == 0; pw <<= 1) {
            // conv with pw * pw size
            conv(pw-1, idx-pw+1, pw);
            if (pw*2 != idx+2) {
                conv(idx-pw+1, pw-1, pw);
            }
        }

        return result[idx++];
    }
};
