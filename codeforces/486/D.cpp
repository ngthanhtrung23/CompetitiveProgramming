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
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 2011;
const long long MOD = 1000000007LL;
int n, d, a[MN], res;
long long f[MN];
vector<int> ke[MN];

void dfs(int u, int fu, int start, int nn, int ln) {
    f[u] = 1;
    for(int v : ke[u]) {
        if (v == fu) continue;
        if (a[v] < nn || a[v] > ln) continue;
        if (a[v] == nn && v < start) continue;

        // cout << v << ' ';
        dfs(v, u, start, nn, ln);
        f[u] = (f[u] * (f[v] + 1)) % MOD;
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> d >> n) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,n) cin >> a[i];
        FOR(i,2,n) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }

        res = 0;
        FOR(i,1,n) {
            // DEBUG(i);
            memset(f, 0, sizeof f);
            dfs(i, -1, i, a[i], a[i]+d);
            res = (res + f[i]) % MOD;
            // cout << endl;
            // DEBUG(res);
        }
        cout << res << endl;
    }
    return 0;
}
