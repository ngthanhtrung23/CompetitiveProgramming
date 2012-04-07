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

int n, m, BASE, a[311][311], f[611], in[611], out[611];
vector<int> ke[611], source, sink;

ll power(int x, int k) {
    if (!k) return 1 % BASE;
    if (k == 1) return x % BASE;
    ll mid = power(x, k >> 1);
    mid = mid * mid % BASE;
    if (k & 1) return mid * x % BASE;
    else return mid;
}

int dfs(int u) {
    if (f[u] >= 0) return f[u];
    f[u] = 0;
    REP(i,ke[u].size()) {
        int v = ke[u][i];
        f[u] += dfs(v);
        if (f[u] >= BASE) f[u] -= BASE;
    }
    return f[u];
}

int get() {
    int n = source.size();
    bool rev = false;
    FOR(j,1,n) {
        int save = j;
        if (a[j][j] == 0) {
            FOR(i,j+1,n) if (a[i][j]) save = i;
        }
        if (a[save][j] == 0) return 0;
        if (save != j) {
            rev = !rev;
            FOR(k,j,n) swap(a[save][k], a[j][k]);
        }
        
        FOR(i,j+1,n) {
            int x = a[i][j] * power(a[j][j], BASE-2) % BASE;
            FOR(k,j,n) {
                a[i][k] = a[i][k] - a[j][k] * (ll) x % BASE;
                if (a[i][k] < 0) a[i][k] += BASE;
            }
        }
    }
    int res = 1;
    FOR(i,1,n) res = (res * (ll) a[i][i]) % BASE;
    if (rev) res = res * (BASE-1LL) % BASE;
    return res;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d%d", &n, &m, &BASE) == 3) {
        FOR(i,1,n) ke[i].clear();
        int u, v;
        memset(in, 0, sizeof in);
        memset(out, 0, sizeof out);
        while (m--) {
            scanf("%d%d", &u, &v);
            out[u]++; in[v]++;
            ke[v].PB(u);
        }
        source.clear(); sink.clear();
        FOR(i,1,n) {
            if (in[i] == 0 && out[i]) source.PB(i);
            if (out[i] == 0 && in[i]) sink.PB(i);
        }
        
        REP(i,source.size()) {
            int u = source[i];
            memset(f, -1, sizeof f);
            REP(x,source.size()) if (x == i) f[source[x]] = 1; else f[source[x]] = 0;
            
            REP(j,sink.size()) {
                a[i+1][j+1] = dfs(sink[j]);
            }
        }
        
        /*
        cout << "source = "; REP(i,source.size()) cout << source[i] << ' '; puts("");
        cout << "sink = "; REP(i,sink.size()) cout << sink[i] << ' '; puts("");
        REP(i,source.size()) {
            REP(j,sink.size()) cout << a[i+1][j+1] << ' ';
            puts("");
        }
        */
        
        int res = get();
        FOR(i,1,n) if (!in[i] && !out[i]) {
            int a = 0, b = 0;
            REP(x,source.size()) if (source[x] < i) a++;
            REP(x,sink.size()) if (sink[x] < i) b++;
            if (a % 2 != b % 2) res = BASE - res;
        }
        printf("%d\n", res % BASE);
    }
    return 0;
}
