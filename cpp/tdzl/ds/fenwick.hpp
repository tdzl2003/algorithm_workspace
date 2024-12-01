#pragma once

// 树状数组
// 支持逆元的操作可以实现区间求和
// 不支持逆元的操作也可以实现前缀求和
// source: https://github.com/atcoder/ac-library/blob/master/atcoder/fenwicktree.hpp

template <class T>
struct fenwick_tree {
  public:
    fenwick_tree() : _n(0) {}
    explicit fenwick_tree(int n) : _n(n), data(n) {}

    int size() {
        return _n;
    }

    void add(int p, T x) {
        assert(0 <= p && p < _n);
        p++;
        while (p <= _n) {
            data[p - 1] += x;
            p += p & -p;
        }
    }

    T sum(int l, int r) {
        assert(0 <= l && l <= r && r <= _n);
        return sum(r) - sum(l);
    }

    T sum(int r) {
        T s = 0;
        while (r > 0) {
            s += data[r - 1];
            r -= r & -r;
        }
        return s;
    }

  private:
    int _n;
    std::vector<T> data;
};
