//#pragma comment(linker, "/STACK:66777216")
#include <iomanip>
#include <sstream>
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
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int n, mark[111], f[111][3], tr[111];
vector<int> ke[111];

void dfs1(int u, int fu) {
    f[u][0] = 0;
    f[u][1] = 1;
    f[u][2] = 0;
    
    int nn = 1000111;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        dfs1(v, u);
        
        f[u][0] += min(f[v][2], f[v][1]);
        
        f[u][1] += min(f[v][0], f[v][1]);
        f[u][2] += min(f[v][2], f[v][1]);
        if (f[v][1] - f[v][2] < nn) {
            tr[u] = v;
            nn = f[v][1] - f[v][2];
        }
    }
    f[u][2] += max(nn,0);
}

void dfs2(int u, int fu, int need) {
    if (need == 1) {
        mark[u] = 1;
    }
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        
        if (need == 1) {
            if (f[v][0] < f[v][1]) dfs2(v, u, 0);
            else dfs2(v, u, 1);
        }
        else if (need == 0) {
            if (f[v][2] < f[v][1]) dfs2(v, u, 2);
            else dfs2(v, u, 1);
        }
        else {
            if (v == tr[u]) dfs2(v, u, 1);
            else {
                if (f[v][2] < f[v][1]) dfs2(v, u, 2);
                else dfs2(v, u, 1);
            }
        }
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    int n;
    while (scanf("%d", &n) == 1) {
        if (n == 1) {
            puts("1");
            continue;
        }
        FOR(i,1,n) ke[i].clear();
        
        FOR(i,2,n) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].PB(v); ke[v].PB(u);
        }
        dfs1(1,-1);
        
        int res = min(f[1][2], f[1][1]);
        
        memset(mark, 0, sizeof mark);
        if (f[1][2] == res) dfs2(1,-1,2);
        else dfs2(1,-1,1);
        
        FOR(i,1,n) printf("%d ", mark[i]);
        puts("");
    }
    return 0;
}