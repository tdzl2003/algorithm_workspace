#pragma once
#include "../utility/md_vector.hpp"

/*
* 基础实现版trie，空间复杂度为 |S|L，适合字符集较小的场合。O(1)查询。
*/
template<size_t _ABSize, char _CharBase>
struct trie_node_base {
    static const size_t ABSize = _ABSize;
    static const char CharBase = _CharBase;

    array<int, ABSize> children;
    size_t matchCnt, depth;

    trie_node_base() {
        children.fill(-1);
        matchCnt = 0;
        depth = 0;
    }
};

template <typename NodeType>
class trie {
public:
    static const size_t ABSize = NodeType::ABSize;
    static const char CharBase = NodeType::CharBase;
    
    vector<NodeType> nodes;

    trie() {
        nodes.resize(1);
    }

    trie(const vector<string>& dict) {
        nodes.resize(1);
        for (const auto& v : dict) {
            insert(v);
        }
    }

    NodeType& insert(const string& s) {
        int curr = 0;
        for (auto ch : s) {
            auto& cnode = nodes[curr];
            if (cnode.children[ch - CharBase] >= 0) {
                curr = cnode.children[ch - CharBase];
            }
            else {
                curr = cnode.children[ch - CharBase] = nodes.size();
                int nextdepth = cnode.depth + 1;
                nodes.push_back(NodeType());
                nodes.back().depth = nextdepth;
            }
        }
        ++nodes[curr].matchCnt;
        return nodes[curr];
    }

    struct state {
        trie* trie_;
        int value_;
        state(trie* t, int value= 0): trie_(t), value_(value) {}

        bool valid() {
            return value_ >= 0;
        }
        size_t match() {
            return valid() && trie_->nodes[value_].matchCnt;
        }
        size_t depth() {
            return valid() ? trie_->nodes[value_].depth : 0;
        }
        state step(char ch) {
            if (valid()) {
                return state(trie_, trie_->nodes[value_].children[ch - CharBase]);
            }
            return *this;
        }
    };

    auto make_state() {
        return state(this);
    }
};
