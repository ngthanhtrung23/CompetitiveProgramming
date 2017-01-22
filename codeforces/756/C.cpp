
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

const int MN = 100111;

int n, x[MN];

struct Node {
    int lazy, ln;
} it[MN * 4];

void down(int i) {
    if (it[i].lazy) {
        int t = it[i].lazy; it[i].lazy = 0;

        it[i<<1].lazy += t;
        it[i<<1].ln += t;

        it[i<<1|1].lazy += t;
        it[i<<1|1].ln += t;
    }
}
void up(int i) {
    assert(!it[i].lazy);
    it[i].ln = max(it[i<<1].ln, it[i<<1|1].ln);
}

void update(int i, int l, int r, int u, int v, int val) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].lazy += val;
        it[i].ln += val;
        return ;
    }
    down(i);
    int mid = (l + r) >> 1;
    update(i<<1, l, mid, u, v, val);
    update(i<<1|1, mid+1, r, u, v, val);

    up(i);
}
int get(int i, int l, int r) {
    if (l == r) {
        assert(it[i].ln > 0);
        return l;
    }
    down(i);

    int mid = (l + r) >> 1;
    if (it[i<<1|1].ln > 0) return get(i<<1|1, mid+1, r);
    else {
        return get(i<<1, l, mid);
    }

    up(i);
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        memset(it, 0, sizeof it);
        FOR(i,1,n) {
            int pos; GI(pos);
            int typ; GI(typ);
            if (typ == 1) {
                update(1, 1, n, 1, pos, +1);
                GI(x[pos]);
            }
            else {
                update(1, 1, n, 1, pos, -1);
            }

            // find sol
            if (it[1].ln <= 0) puts("-1");
            else {
                int res = get(1, 1, n);
                printf("%lld\n", x[res]);
            }
        }
    }
}
