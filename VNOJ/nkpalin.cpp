#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

string s;
int f[2011][2011];

void trace(int i, int j) {
    if (i > j) return;

    if (i == j) {
        cout << s[i];
        return;
    }

    if (s[i] == s[j]) {
        cout << s[i];
        trace(i+1, j-1);
        cout << s[j];
        return;
    }

    if (f[i][j] == f[i+1][j]) {
        trace(i+1, j);
    } else {
        assert(f[i][j] == f[i][j-1]);
        trace(i, j-1);
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    while (cin >> s) {
        int n = s.length();
        s = " " + s + " ";

        memset(f, 0, sizeof f);

        // f[i][j] = max length palindrome subseq
        for (int i = n; i >= 1; i--) {
            for (int j = i; j <= n; j++) {
                if (i == j) {
                    f[i][j] = 1;
                } else if (s[i] == s[j]) {
                    f[i][j] = f[i+1][j-1] + 2;
                } else {
                    f[i][j] = max(f[i+1][j], f[i][j-1]);
                }
            }
        }
        // cout << f[1][n] << endl;
        trace(1, n);
        cout << endl;
    }
    return 0;
}
