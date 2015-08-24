
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;
const int MN = 1011;
struct DSU {
    int lab[MN];
    void init(int n) {
        REP(i,n+1) lab[i] = -1;
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

int n, m;
string a[MN];

pair< int, pair<int,int> > c[MN * MN];

int get(const string& a, const string& b) {
    int res = 0;
    REP(i,m)
        res = max(res, abs(a[i] - b[i]));
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) cin >> a[i];
        int k = 0;
        FOR(i,1,n) FOR(j,i+1,n) {
            ++k;
            c[k] = make_pair(get(a[i], a[j]), make_pair(i, j));
        }
        sort(c+1, c+k+1);
        DSU dsu; dsu.init(n+1);
        int res = 0;
        FOR(i,1,k) {
            int u = c[i].second.first, v = c[i].second.second;
            if (dsu.getRoot(u) == dsu.getRoot(v)) continue;

            dsu.merge(u, v);
            res = c[i].first;
        }
        cout << res << endl;
    }
}
