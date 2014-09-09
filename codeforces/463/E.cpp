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

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;
const int MV = 2000111;

int sieve[MV];
int n, q, h[MN], a[MN], res[MN];
vector<int> ke[MN];
vector<int> ls[MV];

void init() {
    FOR(i,2,2000) if (!sieve[i]) {
        int j = i*i;
        while (j < MV) {
            sieve[j] = i;
            j += i;
        }
    }
}

void dfs(int u, int fu) {
    int saveu = u;
    u = a[u];
    while (u > 1) {
        int p = (sieve[u]) ? sieve[u] : u;

        if (ls[p].size() && ls[p].back() != saveu) {
            int v = ls[p].back();
            if (0 > res[saveu] || h[v] > h[res[saveu]]) {
                res[saveu] = v;
            }
        }

        if (ls[p].size() == 0 || ls[p].back() != saveu) {
            ls[p].push_back(saveu);
        }

        u /= p;
    }
    u = saveu;

    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        h[v] = h[u] + 1;
        dfs(v, u);
    }

    u = a[u];
    while (u > 1) {
        int p = (sieve[u]) ? sieve[u] : u;
        if (ls[p].size() && ls[p].back() == saveu)
            ls[p].pop_back();
        u /= p;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    init();
    while (cin >> n >> q) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        memset(res, -1, sizeof res);
        dfs(1, -1);
        REP(i,MV)
            if (ls[i].size()) cout << "???" << i << endl;
        while (q--) {
            int typ; cin >> typ;
            if (typ == 1) {
                int u;
                cin >> u;
                cout << res[u] << endl;
            } else {
                int u, w; cin >> u >> w;
                a[u] = w;
                memset(res, -1, sizeof res);
                dfs(1, -1);
                REP(i,MV)
                    if (ls[i].size()) cout << "??? " << i << endl;
            }
        }
    }
    return 0;
}

