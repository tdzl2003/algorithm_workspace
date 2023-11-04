#pragma once

template<typename mint>
class s_hash {
public:
    string s;
    vector<mint> hash, pow;

    s_hash(const string& str, int base) : s(str) {
        int n = str.size();
        hash.resize(n + 1);
        pow.resize(n + 1);

        pow[0] = 1;
        hash[0] = 0;
        for (int i = 0; i < n; i++) {
            pow[i + 1] = pow[i] * base;
            hash[i + 1] = hash[i] * base + str[i];
        }
    }

    mint hashed(int start, int end) {
        return (hash[end] - hash[start] * pow[end - start]);
    }
};
