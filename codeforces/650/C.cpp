#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 1000111;
int m, n, mn, a[MN];
int lab[MN];
struct DSU {
    void init(int n) {
        memset(lab, -1, sizeof lab);
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};
int res[MN];

pair<int,int> cur[MN], order[MN];
int row[MN], col[MN];

vector<int> ls[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%lld%lld", &m, &n) == 2) {
        mn = m * n;
        REP(i,mn) scanf("%lld", &a[i]);
        DSU dsu; dsu.init(mn);
        // for each row, connect equal numbers
        REP(i,m) {
            int k = 0;
            FOR(x,i*n,i*n+n-1) {
                cur[k++] = make_pair(a[x], x);
            }
            sort(cur, cur+k);
            int x = 0;
            while (x < k) {
                int y = x;
                while (y + 1 < k && cur[y+1].first == cur[y].first) ++y;
                FOR(t,x+1,y) dsu.merge(cur[t-1].second, cur[t].second);
                x = y + 1;
            }
        }
        // for each col, connect equal numbers
        REP(j,n) {
            int k = 0;
            for(int x = j; x < mn; x += n) {
                cur[k++] = make_pair(a[x], x);
            }
            sort(cur, cur+k);
            int x = 0;
            while (x < k) {
                int y = x;
                while (y + 1 < k && cur[y+1].first == cur[y].first) ++y;
                FOR(t,x+1,y) dsu.merge(cur[t-1].second, cur[t].second);
                x = y + 1;
            }
        }
        // process all numbers in increasing order
        REP(i,mn) order[i] = make_pair(a[i], i);
        sort(order, order+mn);

        REP(i,mn) ls[i].clear();
        REP(i,mn) {
            int r = dsu.getRoot(i);
            ls[r].push_back(i);
        }

        memset(row, 0, sizeof row);
        memset(col, 0, sizeof col);
        REP(i,mn) {
            int p = order[i].second;
            if (p != dsu.getRoot(p)) continue;

            int val = 0;
            for(int x : ls[p]) {
                int r = x / n, c = x % n;

                val = max(val, max(row[r], col[c]));
            }
            ++val;
            for(int x : ls[p]) {
                int r = x / n, c = x % n;
                res[x] = val;
                row[r] = col[c] = val;
            }
        }
        // fill the empty positions
        for(int i = 0; i < mn; i += n) {
            REP(j,n) printf("%lld ", res[i+j]);
            puts("");
        }
    }
}