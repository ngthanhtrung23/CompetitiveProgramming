#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

struct Block {
    int h, c, a;
} blocks[411];
int nBlock;

bool operator < (const Block& a, const Block& b) {
    return a.a < b.a;
}

bitset<40111> f[411];

int32_t main() {
    ios::sync_with_stdio(0);
    cin >> nBlock;
    for (int i = 1; i <= nBlock; i++) {
        cin >> blocks[i].h >> blocks[i].a >> blocks[i].c;
    }
    sort(blocks+1, blocks+nBlock+1);

    f[0][0] = 1;
    for (int i = 0; i < nBlock; i++) {
        for (int h = 0; h <= 40000; h++) {
            if (f[i][h]) {
                for (int x = 0; x <= blocks[i+1].c; x++) {
                    int new_h = h + blocks[i+1].h * x;
                    if (new_h <= blocks[i+1].a) {
                        f[i+1][new_h] = true;
                    }
                }
            }
        }
    }

    for (int res = 40000; res >= 0; res--) {
        if (f[nBlock][res]) {
            cout << res << endl;
            break;
        }
    }
    return 0;
}
