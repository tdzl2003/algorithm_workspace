#pragma once
#include "../common.hpp"

vector<string> split(string content, string sep) {
    vector<string> ret;
    size_t last = 0;
    while (last < content.size()) {
        size_t next = content.find(sep, last);
        if (next == string::npos) {
            ret.push_back(content.substr(last));
            break;
        }
        ret.push_back(content.substr(last, next - last));
        last = next + sep.size();
    }
    return ret;
}
