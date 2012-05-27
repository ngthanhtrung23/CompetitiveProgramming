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
#include <bitset>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i<_a; ++i)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
#define PR0(a,n) cout << #a << " = "; REP(i,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int n;
vector< pair<int,int> > ke[100111];
int fat[20][100111], ind[100111], cnt[20][100111], h[100111];

void dfs(int u, int fu) {
    REP(i,ke[u].size()) {
        int v = ke[u][i].F;
        if (v == fu) continue;
        
        ind[v] = ke[u][i].S;
        fat[0][v] = u;
        h[v] = h[u] + 1;
        dfs(v, u);
    }
}

void init() {
    FOR(t,1,18) {
        FOR(u,1,n) if (fat[t-1][u] != -1) {
            int v = fat[t-1][u];
            fat[t][u] = fat[t-1][v];
        }
    }
}

void update(int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    if (h[u] != h[v]) {
        FORD(i,18,0) {
            int x = fat[i][u];
            if (x > 0 && h[x] >= h[v]) {
                cnt[i][u]++;
                u = x;
            }
        }
    }
    
    if (u != v) {
        FORD(i,18,0)
        if (fat[i][u] != fat[i][v]) {
            cnt[i][u]++;
            cnt[i][v]++;
            u = fat[i][u];
            v = fat[i][v];
        }
        cnt[0][u]++;
        cnt[0][v]++;
    }
}

int res[100111];

void solve() {
    FORD(i,18,1)
    FOR(u,1,n) if (cnt[i][u]) {
        int v = fat[i-1][u];
        cnt[i-1][u] += cnt[i][u];
        if (v > 0) cnt[i-1][v] += cnt[i][u];
    }
    
    FOR(i,2,n) res[ind[i]] = cnt[0][i];
    FOR(i,1,n-1) printf("%d ", res[i]); puts("");
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) ke[i].clear();
        memset(cnt, 0, sizeof cnt);
        memset(fat, -1, sizeof fat);
        
        FOR(turn,1,n-1) {
            int u, v;
            scanf("%d%d", &u, &v);
            ke[u].PB(MP(v,turn));
            ke[v].PB(MP(u,turn));
        }
        dfs(1, -1);
        init();
        
        int q; scanf("%d", &q);
        while (q--) {
            int u, v; scanf("%d%d", &u, &v);
            update(u,v);
        }
        solve();
    }
    return 0;
}
