#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 50111;

int a[MN];
int ln[MN * 4];
int nn[MN * 4];

void init(int i, int l, int r) {
    if (l == r) {
        ln[i] = nn[i] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    init(i*2, l, mid);
    init(i*2 + 1, mid+1, r);

    ln[i] = max(ln[i*2], ln[i*2+1]);
    nn[i] = min(nn[i*2], nn[i*2+1]);
}

const int INF = 1000111000;
int getMax(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return -INF;
    if (u <= l && r <= v) return ln[i];

    int mid = (l + r) / 2;
    return max(
            getMax(i*2, l, mid, u, v),
            getMax(i*2+1, mid+1, r, u, v));
}

int getMin(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return INF;
    if (u <= l && r <= v) return nn[i];

    int mid = (l + r) / 2;
    return min(
            getMin(i*2, l, mid, u, v),
            getMin(i*2+1, mid+1, r, u, v));
}

int32_t main() {
    ios::sync_with_stdio(0);
    int n, q;
    while (cin >> n >> q) {
        for (int i = 1; i <= n; i++) cin >> a[i];
        init(1, 1, n);

        while (q--) {
            int l, r; cin >> l >> r;
            cout << getMax(1, 1, n, l, r) - getMin(1, 1, n, l, r) << '\n';
        }
    }
    return 0;
}
