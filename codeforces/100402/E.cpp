
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

int f[155][155][2];
vector<int> ke[155];
bool visited[155];
int qu[155], first, last;

int get(int even, int odd, int self) {
    if (f[even][odd][self] >= 0) return f[even][odd][self];

    int& res = f[even][odd][self];

    if (even + odd == 1) return res = 0;
    if (even + odd == 2) return res = 1;

    // use self edge
    if (self) {
        int t = get(even, odd, 1 - self);
        if (t == 0) return res = 1;
    }
    
    // even - even
    if (even >= 2) {
        int t = get(even - 1, odd, self ^ 1);
        if (t == 0) return res = 1;
    }
    // odd - odd
    if (odd >= 2) {
        int t = get(even + 1, odd - 2, self);
        if (t == 0) return res = 1;
    }

    // even - odd
    if (even && odd) {
        int t = get(even - 1, odd, self ^ 1);
        if (t == 0) return res = 1;
    }
    return res = 0;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("points.in", "r", stdin);
    freopen("points.out", "w", stdout);

    memset(f, -1, sizeof f);
    int n, m;
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        memset(visited, 0, sizeof visited);
        int odd = 0, even = 0, self = 0;
        FOR(i,1,n) if (!visited[i]) {
            first = last = 1; qu[1] = i;
            visited[i] = 1;
            while (first <= last) {
                int u = qu[first++];
                for(int v : ke[u]) if (!visited[v]) {
                    visited[v] = 1;
                    qu[++last] = v;
                }
            }
            if (last % 2) ++odd;
            else ++even;

            int sum = last * (last - 1);
            FOR(i,1,last) {
                int u = qu[i];
                sum -= SZ(ke[u]);
            }
            sum /= 2;
            if (sum % 2) self = 1 - self;
        }

        puts(get(even, odd, self) ? "Andrew" : "Betty");
    }
}
