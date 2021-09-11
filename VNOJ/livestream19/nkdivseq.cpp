#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n;
    while (cin >> n) {
        int generated = 0;
        int last = 0;  // last generated number
        for (int step = 1; step <= 10000; step++) {
            int first = last - last % step + step;
            if (first == last) first += step;
            last = first + (step - 1) * step;

            if (generated + step >= n) {
                int k = n - generated;
                cout << first + (k - 1) * step << endl;
                break;
            }
            generated += step;
        }
    }
    return 0;
}
