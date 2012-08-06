#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);
const int MN = 200111;
const long long oo = 1000111000111000111LL;

int n, m, k, trace[MN], lab[MN];
bool need[MN];
vector< pair<int,int> > ke[MN];
long long f[MN];
set< pair<long long, int> > s;

void init(int n) {
    memset(need, false, sizeof need);
    FOR(i,1,n) {
        ke[i].clear();
        f[i] = oo;
        lab[i] = -1;
    }
    s.clear();
}

int getRoot(int u) {
    if (lab[u] < 0) return u;
    else return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    int x = lab[u] + lab[v];
    if (lab[u] < lab[v]) {
        lab[u] = x;
        lab[v] = u;
    }
    else {
        lab[u] = v;
        lab[v] = x;
    }
}

void ijk() {
    while (!s.empty()) {
        int u = s.begin()->S;
        long long l = s.begin()->F;
        s.erase(s.begin());
        if (f[u] != l) continue;

        REP(i,ke[u].size()) {
            int v = ke[u][i].F, c = ke[u][i].S;
            if (f[v] > f[u] + c) {
                f[v] = f[u] + c;
                trace[v] = trace[u];
                s.insert(MP(f[v], v));
            }
        }
    }
    // PR(f, n);
}

pair< long long, pair<int,int> > edges[MN];

void solve() {
    m = 0;
    FOR(u,1,n)
    REP(i,ke[u].size()) {
        int v = ke[u][i].F, c = ke[u][i].S;
        if (trace[v] != trace[u]) {
            edges[++m] = MP(c + f[u] + f[v], MP(trace[u],trace[v]));
        }
    }
    sort(edges+1, edges+m+1);

    long long res = 0;
    FOR(i,1,m) {
        int u = edges[i].S.F, v = edges[i].S.S;
        long long c = edges[i].F;
        u = getRoot(u); v = getRoot(v);
        if (u == v) continue;
        res += c;
        merge(u, v);
    }
    if (!need[1]) {
        res += f[1];
    }
    cout << res << endl;
}

int main() {
    while  (scanf("%d%d", &n, &m) == 2) {
        init(n);
        while (m--) {
            int u, v, c; scanf("%d%d%d", &u, &v, &c);
            ke[u].PB(MP(v,c));
            ke[v].PB(MP(u,c));
        }
        scanf("%d", &k);
        FOR(i,1,k) {
            int u; scanf("%d", &u);
            need[u] = true;
            f[u] = 0;
            trace[u] = u;
            s.insert(MP(0,u));
        }
        ijk();
        solve();
    }
    return 0;
}
