#pragma once
#include "../common.hpp"

struct bit_trie {
	struct node {
		int left, right;
	};

	vector<node> nodes = { {-1, -1} };
	unsigned int base = 0;

private:
	void _add(unsigned int v, int d = 31, int r = 0) {
		if (d == -1) {
			return;
		}
		auto& curr = nodes[r];
		if (v & (1 << d)) {
			if (curr.right < 0) {
				curr.right = nodes.size();
				nodes.push_back({ -1, -1 });
			}
			return _add(v, d - 1, nodes[r].right);
		}
		else {
			if (curr.left < 0) {
				curr.left = nodes.size();
				nodes.push_back({ -1, -1 });
			}
			return _add(v, d - 1, nodes[r].left);
		}
	}
	unsigned int _max(unsigned int v = 0, int d = 31, int r =0) {
		if (d == -1) {
			return v;
		}
		auto& curr = nodes[r];
		auto bit = (1 << d);
		if (base & bit) {
			if (curr.left > 0) {
				return _max(v | bit, d - 1, curr.left);
			}
			return _max(v, d - 1, curr.right);
		}
		else {
			if (curr.right > 0) {
				return _max(v | bit, d - 1, curr.right);
			}
			return _max(v, d - 1, curr.left);
		}
	}
public:
	void add(unsigned int v) {
		_add(v ^ base);
	}

	unsigned int max() {
		return _max();
	}
	unsigned int min() {
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
