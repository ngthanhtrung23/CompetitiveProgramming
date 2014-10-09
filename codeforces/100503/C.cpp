#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;

struct DSU {
    int lab[MN];
    void init() {
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
} dsu;

struct Edge {
    int u, v, r, p, id;

    void read() { cin >> u >> v >> r >> p; }
} edges[MN];

bool operator < (const Edge &a, const Edge &b) {
    if (a.r != b.r) return a.r < b.r;
    return a.p < b.p;
}

int c[MN * 2], n;

void RR() {
    int s = 0;
    FOR(i,1,n) {
        c[++s] = edges[i].u;
        c[++s] = edges[i].v;
    }
    sort(c+1, c+s+1);
    s = unique(c+1, c+s+1) - c - 1;
    // PR(c, s);

    FOR(i,1,n) {
        edges[i].u = lower_bound(c+1, c+s+1, edges[i].u) - c;
        edges[i].v = lower_bound(c+1, c+s+1, edges[i].v) - c;
    }
}

bool good[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    while (cin >> n) {
        FOR(i,1,n) {
            edges[i].read();
            edges[i].id = i;
        }
        RR();

        dsu.init();

        sort(edges+1, edges+n+1);

        long long res = 0;
        vector<int> all;

        memset(good, false, sizeof good);
        FORD(i,n,1) {
            int u = dsu.getRoot(edges[i].u), v = dsu.getRoot(edges[i].v);
            if (u == v) continue;

            dsu.merge(u, v);

            res += edges[i].p;
            good[edges[i].id] = true;
            all.push_back(edges[i].id);
        }

        cout << res << endl;
        FOR(i,1,n) if (!good[i]) cout << i << ' ';
        FOR(i,1,n) if (good[i]) cout << i << ' ';
        cout << endl;
    }
    return 0;
}
