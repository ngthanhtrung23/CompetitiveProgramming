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
#define PR(a,n) cout << #a << " = "; FOR(i,0,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int n, k, f[50111][511], fat[50111];
vector<int> ke[50111];
ll res;

void dfs(int u, int fu) {
    f[u][0] = 1;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        if (v == fu) continue;
        f[u][1]++;
        fat[v] = u;
        dfs(v, u);
        FOR(x,2,k) f[u][x] += f[v][x-1];
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d%d", &n, &k);
    int u, v;
    FOR(i,2,n) {
        scanf("%d%d", &u, &v);
        ke[u].PB(v); ke[v].PB(u);
    }
    res = 0;
    dfs(1, -1);
    FOR(u,1,n) {
//        PR(f[u], k);
        res += f[u][k];
        ll cur = 0;
        REP(i,ke[u].size()) {
            int v = ke[u][i];
            if (v == fat[u]) continue;
            
            FOR(x,1,k-1) {
                cur += f[v][x-1] * (ll) (f[u][k-x] - f[v][k-x-1]);
            }
        }
        res += cur / 2;
//        cout << res << endl;
    }
    cout << res;
    return 0;
}
