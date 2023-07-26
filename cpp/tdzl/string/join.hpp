#pragma once
#include "../common.hpp"

string join(const vector<string>& words, string sep) {
    string ret;
    for (auto i = 0; i < words.size(); i++) {
        if (i) {
            ret.insert(ret.end(), sep.begin(), sep.end());
        }
        auto& w = words[i];
        ret.insert(ret.end(), w.begin(), w.end());
    }
    return ret;
}
