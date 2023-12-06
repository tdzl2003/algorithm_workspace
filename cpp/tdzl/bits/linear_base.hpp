#pragma once

template <typename UInt = unsigned int, int bits = 32>
struct linear_base {
    array<UInt, bits> bases;

    linear_base(){
        bases.fill(UInt());
    }

    void add(UInt x) {
        for (int i = bits - 1; i >= 0; i--) {
            x = min(x, x ^ bases[i]);
        }
        if (!x) return;
        for (int i = bits - 1; i >= 0; i--) {
            if (x & (1 << i)) {
                bases[i] = x;
                break;
            }
            bases[i] = min(bases[i], bases[i] ^ x);
        }
    }

    linear_base& operator*=(linear_base& other) {
        for (auto v : other.bases) {
            add(v);
        }
        return *this;
    }
    UInt max_xor() {
        UInt ret = UInt();
        for (int i = bits - 1; i >= 0; i--) {
            ret = ret ^ bases[i];
        }
        return ret;
    }
    UInt kth(UInt k) {
        UInt ret;
        for (int i = 0; i < bits; i++) {
            if (bases[i]) {
                if (k & 1) {
                    ret ^= bases[i];
                }
                k >>= 1;
            }
        }
        assert(k == 0);
    }
};
