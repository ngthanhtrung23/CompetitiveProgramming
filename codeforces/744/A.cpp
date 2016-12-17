
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
int GI(ll& x) { return scanf("%lld", &x); }

const int MN = 100111;

vector<int> ke[MN];
int n, k;
int good[MN];
int qu[MN], visited[MN];
int res;

int bfs(int start) {
    int first = 1, last = 1;
    qu[1] = start;
    visited[start] = 1;

    while (first <= last) {
        int u = qu[first++];
        for(int v : ke[u]) {
            if (visited[v]) continue;

            visited[v] = true;
            qu[++last] = v;
        }
    }

    int x = last;
    res += x * (x - 1) / 2;

    int ne = 0;
    FOR(i,1,x) ne += SZ(ke[qu[i]]);

    res -= ne / 2;
    return x;
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        int m; GI(m); GI(k);
        FOR(i,1,k) GI(good[i]);

        FOR(i,1,n) ke[i].clear();

        while (m--) {
            int u, v; GI(u); GI(v);
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        int best = 0;
        res = 0;
        memset(visited, 0, sizeof visited);
        FOR(i,1,k) {
            best = max(best, bfs(good[i]));
        }

        FOR(i,1,n) if (!visited[i]) {
            int x = bfs(i);
            res += best * x;

            best += x;
        }
        cout << res << endl;
    }
}
