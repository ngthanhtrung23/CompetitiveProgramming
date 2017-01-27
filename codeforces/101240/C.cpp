
#include <sstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 800111;
const int MOD = 1e9 + 7;

map<int,int> ways[MN]; // [wands][zombies] --> ways
int n;

void add(int& f, int a) {
    f = (f + a) % MOD;
}

struct Node {
    int x[2][2];

    void one(int l) {
        memset(x, 0, sizeof x);
        x[0][0] = ways[l][l];
        x[1][0] = ways[l-1][l];
        x[0][1] = ways[l+1][l];
    }
} it[MN * 4];

Node operator + (const Node& a, const Node& b) {
    Node res;
    memset(res.x, 0, sizeof res.x);

    REP(u,2) REP(v,2) {
        res.x[u][v] = (a.x[u][0] * b.x[0][v]
                + a.x[u][1] * b.x[1][v]) % MOD;
    }

    return res;
}

void build(int i, int l, int r) {
    if (l == r) {
        it[i].one(l);
        return ;
    }

    int mid = (l + r) >> 1;
    build(i<<1, l, mid);
    build(i<<1|1, mid+1, r);

    it[i] = it[i<<1] + it[i<<1|1];
}

void update(int i, int l, int r, int u) {
    if (u < l || r < u) return;
    if (l == r) {
        it[i].one(l);
        return ;
    }

    int mid = (l + r) >> 1;
    update(i<<1, l, mid, u);
    update(i<<1|1, mid+1, r, u);

    it[i] = it[i<<1] + it[i<<1|1];
}

int S[MN], W[MN], Z[MN], D[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        int n, q; cin >> n >> q;

        FOR(i,0,n+1) ways[i].clear();

        int aw, bw; cin >> W[1] >> aw >> bw;
        FOR(i,2,q) W[i] = ((aw * W[i-1] + bw) % n) + 1;

        int ad, bd; cin >> D[1] >> ad >> bd;
        FOR(i,2,q) {
            D[i] = (ad * D[i-1] + bd) % 3;
        }
        FOR(i,1,q) {
            Z[i] = max(1LL, min(n, W[i] + D[i] - 1));
        }

        int as, bs; cin >> S[1] >> as >> bs;
        FOR(i,2,q) {
            S[i] = ((as * S[i-1] + bs) % 1000000000) + 1;
        }

        FOR(i,1,n) ways[i][i] = 1;
        build(1, 1, n);

        int res = 0;
        FOR(i,1,q) {
            add(ways[W[i]][Z[i]], S[i]);
            update(1, 1, n, Z[i]);

            int cur = 0;
            REP(u,2) REP(v,2)
                add(cur, it[1].x[u][v]);

            add(res, cur);
        }
        cout << "Case #" << test << ": " << res << endl;
    }
}
