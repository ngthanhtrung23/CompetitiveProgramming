#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

const int MN = 50111;
const int INF = 1e10;

int ln[MN * 8];
int lazy[MN * 8];

void down(int i) {
    if (!lazy[i]) return;

    lazy[i*2] += lazy[i];
    lazy[i*2+1] += lazy[i];

    ln[i*2] += lazy[i];
    ln[i*2+1] += lazy[i];

    lazy[i] = 0;
}

// node i contain info of [l, r]
// query [u, v]
int get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) {
        // [u, v] and [l, r] doesn't intersect
        return -INF;
    }
    if (u <= l && r <= v) {
        // [l, r] inside [u, v]
        return ln[i];
    }

    down(i);
    int mid = (l + r) / 2;
    return max(
            get(i*2, l, mid, u, v),
            get(i*2 + 1, mid+1, r, u, v));
}

void update(int i, int l, int r, int u, int v, int k) {
    if (v < l || r < u) {
        return;
    }
    if (u <= l && r <= v) {
        lazy[i] += k;
        ln[i] += k;
        return;
    }

    down(i);

    int mid = (l + r) / 2;
    update(i*2, l, mid, u, v, k);
    update(i*2+1, mid+1, r, u, v, k);

    ln[i] = max(ln[i*2], ln[i*2+1]);
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int n, nUpdate; cin >> n >> nUpdate;
    while (nUpdate--) {
        int u, v, k; cin >> u >> v >> k;
        update(1, 1, n, u, v, k);
    }

    int nQuery; cin >> nQuery;
    while (nQuery--) {
        int u, v; cin >> u >> v;
        cout << get(1, 1, n, u, v) << '\n';
    }
    return 0;
}
