#include "bits/stdc++.h"
using namespace std;

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0);
    stringstream ss;
    for (int i = 1; i <= 100000; i++) {
        ss << i;
    }
    string s = ss.str();

    string n;
    while (cin >> n) {
        cout << s.find(n) + 1 << endl;
    }
    return 0;
}
