
#include <sstream>
#include <fstream>
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
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define PI (2 * acos((double)0))
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define y0 u9cqu3jioajc

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 100111;

struct Barrier {
    int row, s;
    int l, r;
    int drop;

    void read() {
        GI(row);
        GI(l); GI(r);
        GI(s);
    }
} barriers[MN];

set< pair<int,int> > it[MN * 4];

void build(int i, int l, int r) {
    it[i].clear();
    if (l == r) return ;
    int mid = (l + r) >> 1;
    build(i<<1, l, mid);
    build(i<<1|1, mid+1, r);
}

void add(int i, int l, int r, int u, int v, int h, int id) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].insert(make_pair(h, id));
        return ;
    }
    int mid = (l + r) >> 1;
    add(i<<1, l, mid, u, v, h, id);
    add(i<<1|1, mid+1, r, u, v, h, id);
}

void remove(int i, int l, int r, int u, int v, int h, int id) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].erase(make_pair(h, id));
        return ;
    }
    int mid = (l + r) >> 1;
    remove(i<<1, l, mid, u, v, h, id);
    remove(i<<1|1, mid+1, r, u, v, h, id);
}

pair<int,int> NONE = make_pair(-1, -1);

pair<int,int> get(int i, int l, int r, int col) {
    if (col < l || r < col) return NONE;

    pair<int,int> res = NONE;
    if (!it[i].empty()) {
        res = max(res, *it[i].rbegin());
    }
    if (l == r) return res;

    int mid = (l + r) >> 1;
    res = max(res, get(i<<1, l, mid, col));
    res = max(res, get(i<<1|1, mid+1, r, col));
    return res;
}

int nBarrier, h, nCol;

int get(int col) {
    auto p = get(1, 1, nCol, col);
    if (p == NONE) return 1;

    return barriers[p.second].drop;
}


vector< pair<int,int> > events;
const int MOD = 1e9 + 7;

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(h) == 1) {
        GI(nCol); GI(nBarrier);
        FOR(i,1,nBarrier) barriers[i].read();

        build(1,1,nCol);

        events.clear();
        FOR(i,1,nBarrier) {
            // appear
            events.emplace_back(barriers[i].row, +i);
            // disappear
            int t = barriers[i].row + barriers[i].s + 1;
            if (t <= h + 1) {
                events.emplace_back(t, -i);
            }
        }
        sort(ALL(events));

        for(auto event : events) {
            if (event.second > 0) {
                // add barrier
                int i = event.second;

//                cerr << "+ " << i << endl;

                int x, y;  // positions of 2 new balls
                if (barriers[i].l == 1) {
                    x = y = barriers[i].r + 1;
                } else if (barriers[i].r == nCol) {
                    x = y = barriers[i].l - 1;
                } else {
                    x = barriers[i].l - 1;
                    y = barriers[i].r + 1;
                }

                barriers[i].drop = (get(x) + get(y)) % MOD;
//                DEBUG(barriers[i].drop);

                add(1, 1, nCol, barriers[i].l, barriers[i].r, barriers[i].row, i);
            }
            else {
                // remove barrier
                int i = -event.second;
//                cerr << "- " << i << endl;
                remove(1, 1, nCol, barriers[i].l, barriers[i].r, barriers[i].row, i);
            }
        }

        int res = 0;
        FOR(i,1,nCol) {
            res = (res + get(i)) % MOD;
//            cerr << i << " -> " << get(i) << endl;
        }
//        DEBUG(res);
        cout << res << endl;
    }
    return 0;
}
