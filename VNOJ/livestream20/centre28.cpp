// number of shortest path: 1 -> i: cnt1[i]
// number of shortest path: N -> i: cntN[i]
//
// number of shortest path 1 -> N, going through u
// = cnt1[u] * cntN[u]
//
// u can be deleted iff:
// - d1[u] + dN[u] != d1[N]
// - cnt1[N] != cnt1[u] * cntN[u]

#include "bits/stdc++.h"
using namespace std;

#define int long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())

struct Hash {
    int x, y;

    Hash() {}
    Hash(int _x, int _y) : x(_x), y(_y) {}
};

const int MOD = 1e9 + 7;
Hash operator + (const Hash& a, const Hash& b) {
    return Hash(
            a.x + b.x,
            (a.y + b.y) % MOD);
}

Hash operator * (const Hash& a, const Hash& b) {
    return Hash(
            a.x * b.x,
            (a.y * b.y) % MOD);
}

bool operator == (const Hash& a, const Hash& b) {
    return a.x == b.x
        && a.y == b.y;
}

bool operator != (const Hash& a, const Hash& b) {
    return !(a == b);
}

const int MN = 30111;
int d1[MN], dN[MN];
Hash cnt1[MN], cntN[MN];
int n, m;

vector< pair<int, int> > edges[MN];

void dijkstra(int start, int d[], Hash cnt[]) {
    for (int i = 1; i <= n; i++) {
        d[i] = (int) 1e15;
        cnt[i] = {0, 0};
    }

    d[start] = 0;
    cnt[start] = {1, 1};
    set< pair<int,int> > all;
    all.insert({0, start});

    while (!all.empty()) {
        auto [len, u] = *all.begin();
        all.erase(all.begin());

        if (len != d[u]) continue;

        for (auto [v, cost] : edges[u]) {
            int cur = d[u] + cost;

            if (cur == d[v]) {
                cnt[v] = cnt[v] + cnt[u];
            } else if (cur < d[v]) {
                d[v] = cur;
                cnt[v] = cnt[u];
                all.insert({d[v], v});
            }
        }
    }
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    // input
    cin >> n >> m;
    while (m--) {
        int u, v, cost;
        cin >> u >> v >> cost;
        edges[u].push_back({v, cost});
        edges[v].push_back({u, cost});
    }

    // dijkstra
    dijkstra(1, d1, cnt1);
    dijkstra(n, dN, cntN);

    // output
    vector<int> res;
    for (int i = 2; i <= n-1; i++) {
        if (d1[i] + dN[i] != d1[n]
                || cnt1[i] * cntN[i] != cnt1[n]) {
            res.push_back(i);
        }
    }

    cout << SZ(res) << endl;
    for (int x : res) cout << x << '\n';
    return 0;
}

