#include "./convolution.hpp"

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

        idx++;

        if (idx == 1) {
            result[0] = a * b;
            return result[0];
        }
        if (idx == 2) {
            result[1] = f[0] * b + g[0] * a;
            result[2] = a * b;
            return result[1];
        }

        result[idx - 1] += f[0] * b;
        result[idx] += f[1] * b;
        result[idx - 1] += g[0] * a;
        result[idx] += g[1] * a;

        for (int pw = 2; pw < idx && idx % pw == 0; pw <<= 1) {
            // conv with pw * pw size
            conv(pw, idx - pw, pw);
            if (pw * 2 != idx) {
                conv(idx - pw, pw, pw);
            }
        }

        return result[idx - 1];
    }
};
