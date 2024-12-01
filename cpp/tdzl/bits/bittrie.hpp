#pragma once
#include "../common.hpp"

template <typename UInt = unsigned int, int D = 32>
struct bit_trie {
	struct node {
		int left, right;
        int cnt;
	};

	vector<node> nodes = { {-1, -1, 0} };
	UInt base = 0;
    size_t freeHead = -1;

private:
    size_t alloc() {
        if (freeHead != (size_t)-1) {
            size_t ret = freeHead;
            freeHead = nodes[ret].right;
            nodes[ret] = { -1, -1, 0 };
            return ret;
        }
        size_t ret = nodes.size();
        nodes.push_back({ -1, -1, 0 });
        return ret;
    }
    void free(size_t v) {
        nodes[v].right = freeHead;
        freeHead = v;
    }
	void _add(UInt v, int d, size_t r) {
        ++nodes[r].cnt;

        if (d == -1) {
			return;
		}
		if (v & (1 << d)) {
			if (nodes[r].right == (size_t)-1) {
                nodes[r].right = alloc();
			}
			_add(v, d - 1, nodes[r].right);
		}
		else {
			if (nodes[r].left  == (size_t)-1) {
                nodes[r].left = alloc();
			}
			_add(v, d - 1, nodes[r].left);
		}
	}
    bool _remove(UInt v, int d, size_t r) {
        --nodes[r].cnt;
        if (d >= 0) {
            if (v & (1 << d)) {
                if (_remove(v, d - 1, nodes[r].right)) {
                    nodes[r].right = -1;
                }
            }
            else {
                if (_remove(v, d - 1, nodes[r].left)) {
                    nodes[r].left = -1;
                }
            }
        }
        if (!nodes[r].cnt && r > 0) {
            free(r);
            r = -1;
            return true;
        }
        return false;
    }
	UInt _max(UInt v = 0, int d = 31, size_t r =0) {
		if (d == -1) {
			return v;
		}
		UInt bit = (1 << d);
		if (base & bit) {
			if (nodes[r].left != (size_t)-1) {
				return _max(v | bit, d - 1, nodes[r].left);
			}
			return _max(v, d - 1, nodes[r].right);
		}
		else {
			if (nodes[r].right != (size_t)-1) {
				return _max(v | bit, d - 1, nodes[r].right);
			}
			return _max(v, d - 1, nodes[r].left);
		}
	}
public:
	void add(UInt v) {
		_add(v ^ base, D-1, 0);
	}
    void remove(UInt v) {
        _remove(v^base, D-1, 0);
    }

    UInt max() {
		return _max();
	}
    UInt min() {
		base = ~base;
		int ret = max();
		base = ~base;
		return ~ret;
	}

	void xor_all(unsigned int v) {
		base ^= v;
	}

	unsigned int max_xor(unsigned int v) {
		xor_all(v);
		int ret = max();
		xor_all(v);
		return ret;
	}

};
