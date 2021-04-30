// 2 nhan -> 2 chuong trinh
// 26 chi thi
// 1 xung nhip -> 1 nhan: 1 chi thi; 2 nhan: giong nhau
//
// chuong trinh = list chi thi
//
//
// ABC
// ABB
//
// 1. A
// 2. B
// 3. B
// 4. C
//
// 2 chuong trinh -> time = |s1| + |s2| - |lcs|
//
// Step 1: chia 2n chuong trinh -> n vi xu ly
//   f(mask)
// Step 2: tinh thoi gian

#include "bits/stdc++.h"
using namespace std;

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

int cost[22][22];  // cost[i][j] = time to process i and j
string s[22];

int f[111][111];
int lcs(const string& s1, const string& s2) {
    int l1 = SZ(s1) - 2;
    int l2 = SZ(s2) - 2;

    memset(f, 0, sizeof f);
    for (int i = 1; i <= l1; i++) {
        for (int j = 1; j <= l2; j++) {
            if (s1[i] == s2[j]) {
                f[i][j] = f[i-1][j-1] + 1;
            } else {
                f[i][j] = max(f[i-1][j], f[i][j-1]);
            }
        }
    }
    return f[l1][l2];
}

inline int two(int i) {
    return 1<<i;
}
inline int getBit(int s, int i) {
    return (s>>i) & 1;
}

int g[1<<20];

void update(int& f, int val) {
    if (val < f) f = val;
}

int32_t main() {
    ios::sync_with_stdio(0);
    int n; cin >> n;
    for (int i = 0; i < 2*n; i++) {
        cin >> s[i];
        s[i] = " " + s[i] + " ";
    }

    for (int i = 0; i < 2*n; i++) {
        for (int j = 0; j < 2*n; j++) {
            if (i == j) continue;
            cost[i][j] = SZ(s[i]) + SZ(s[j]) - 4 - lcs(s[i], s[j]);
        }
    }

    memset(g, 0x7f, sizeof g);
    g[0] = 0;

    for (int mask = 0; mask < two(2*n); mask++) {
        for (int i = 0; i < 2*n; i++) {
            if (getBit(mask, i)) continue;

            for (int j = i+1; j < 2*n; j++) {
                if (getBit(mask, j)) continue;

                update(g[mask + two(i) + two(j)],
                        max(g[mask], cost[i][j]));
            }
        }
    }
    cout << g[two(2*n) - 1] << endl;
    return 0;
}
