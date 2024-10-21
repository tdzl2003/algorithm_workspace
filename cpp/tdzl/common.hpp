#pragma once
#ifndef NO_STD_INCLUDES
#include <iostream>
#include <stdio.h>
#include <algorithm>
#include <set>
#include <map>
#include <stack>
#include <vector>
#include <string>
#include <tuple>
#include <unordered_set>
#include <unordered_map>
#include <memory>
#include <math.h>
#include <assert.h>
#include <string.h>
#include <array>
#include <queue>
#include <iomanip>
#include <complex>
#include <stdint.h>
#include <type_traits>
#include <numeric>
using namespace std;
#endif

typedef long long LL;
typedef unsigned long long ULL;
#define REP(i,f,t) for (int i = (f); i < (t); i++)

inline void YesNo(bool flag) {
    if (flag) cout << "Yes" << endl;
    else  cout << "No" << endl;
}

template <typename T1, typename T2>
istream& operator >>(istream& in, pair<T1, T2>& vec) {
    return in >> vec.first >> vec.second;
}

template <typename T>
istream& operator >>(istream& in, vector<T>& vec) {
    for (auto& v : vec) {
        in >> v;
    }
    return in;
}

template <typename T1, typename T2>
ostream& operator <<(ostream& out, const pair<T1, T2>& vec) {
    return out << vec.first << ' ' << vec.second;
}

template <typename T>
ostream& operator <<(ostream& out, const vector<T>& vec) {
    bool flag = false;
    for (const auto& v : vec) {
        if (flag) {
            out << ' ';
        }
        else {
            flag = true;
        }
        out << v;
    }
    return out;
}

typedef long long ll;
typedef unsigned int uint;
typedef unsigned long long ull;

#ifndef ONLINE_JUDGE
void io_redirect() {
    freopen("in.txt", "rt", stdin);
}
#else
void io_redirect() {}
#endif

