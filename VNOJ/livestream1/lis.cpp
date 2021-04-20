#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0);
    int n;
    while (cin >> n) {
        vector<int> a(n);
        for(int& x : a) cin >> x;

        multiset<int> s;
        for (int x : a) {
            auto it = s.lower_bound(x);
            if (it != s.end()) {
                s.erase(it);
            }
            s.insert(x);
        }
        cout << s.size() << '\n';
    }
    return 0;
}
