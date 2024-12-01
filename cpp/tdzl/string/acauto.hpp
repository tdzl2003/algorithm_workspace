#pragma once
#include "../common.hpp"
#include "./trie.hpp"

template<size_t _ABSize, char _CharBase>
struct acauto_node_base : trie_node_base<_ABSize, _CharBase> {
    int parent;
};

template <typename NodeType>
class acauto : public trie<NodeType> {
public:
    using trie<NodeType>::ABSize;
    using trie<NodeType>::CharBase;

    using trie<NodeType>::nodes;

    acauto(const vector<string>& dict) : trie<NodeType>(dict) {
        _buildFailPtr();
    }

    template<typename F>
    void _buildFailPtr(F f) {
        queue<pair<int, int>> q;

        nodes[0].parent = -1;
        for (int i = 0; i < ABSize; i++) {
            if (nodes[0].children[i] >= 0) {
                q.push({ 0, i });
            }
        }

        while (q.size()) {
            int parent = q.front().first, ch = q.front().second;
            q.pop();

            int i = nodes[parent].children[ch];
            int j = nodes[parent].parent;
            for (; j >= 0; j = nodes[j].parent) {
                if (nodes[j].children[ch] >= 0) {
                    break;
                }
            }
            int p = nodes[i].parent = j >= 0 ? nodes[j].children[ch] : 0;
            f(i);

            for (int ch = 0; ch < ABSize; ch++) {
                if (nodes[i].children[ch] >= 0) {
                    q.push({ i, ch });
                }
            }
        }
    }

    void _buildFailPtr() {
        _buildFailPtr([](int) {});
    }


    struct state  {
        acauto* trie_;
        int value_;
        state(acauto* t, int value = 0) : trie_(t), value_(value) {}

        auto& curr() {
            return trie_->nodes[value_];
        }
        size_t match() {
            return trie_->nodes[value_].matchCnt;
        }
        state fail() {
            if (value_) {
                return state(trie_, trie_->nodes[value_].parent);
            }
            return state(trie_, 0);
        }
        size_t depth() {
            return trie_->nodes[value_].depth;
        }
        state step(char ch) {
            int v = value_;
            while (v >= 0) {
                int next = trie_->nodes[v].children[ch - CharBase];
                if (next > 0) {
                    v = next;
                    return state(trie_, v);
                }
                v = trie_->nodes[v].parent;
            }
            v = 0;
            return state(trie_, v);
        }
    };

    auto make_state(int v = 0) {
        return state(this, v);
    }
};
