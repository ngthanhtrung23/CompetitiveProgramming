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

const int MN = 811;
const long long oo = 1000111000111000LL;

int m, n, k, a[MN], b[MN], hasEdge[MN][MN], s, t, tr[MN];
long long c[MN][MN];
vector<int> ke[MN];

bool findPath() {
    memset(tr, -1, sizeof tr);
    queue<int> q; q.push(s);
    tr[s] = -1;

    while (!q.empty()) {
        int u = q.front(); q.pop();
        REP(i,ke[u].size()) {
            int v = ke[u][i];
            if (tr[v] < 0 && c[u][v] > 0) {
                tr[v] = u;
                q.push(v);
            }
        }
    }
    return tr[t] >= 0;
}

long long maxFlow = 0;
void incFlow() {
    long long delta = oo, v = t;
    while (v != s) {
        int u = tr[v];
        delta = min(delta, c[u][v]);
        v = u;
    }

    v = t;
    while (v != s) {
        int u = tr[v];
        c[u][v] -= delta;
        c[v][u] += delta;
        v = u;
    }

    maxFlow += delta;
}

void addEdge(int u, int v, long long fl) {
    c[u][v] = fl;
    ke[u].push_back(v);
    ke[v].push_back(u);
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m >> k) {
        memset(hasEdge, false, sizeof hasEdge);
        FOR(i,1,k) {
            int u, v; cin >> u >> v;
            hasEdge[u][v] = true;
        }
        long long sum = 0;
        FOR(i,1,n) {
            cin >> a[i];
            sum += a[i];
        }
        FOR(i,1,m) {
            cin >> b[i];
            sum += b[i];
        }

        s = 0, t = m + n + 1;
        FOR(i,s,t) ke[i].clear();

        memset(c, 0, sizeof c);
        FOR(i,1,n) addEdge(s, i, a[i]);
        FOR(j,1,m) addEdge(n+j, t, b[j]);

        FOR(i,1,n) FOR(j,1,m) if (!hasEdge[i][j]) {
            addEdge(i, n+j, oo);
        }

        maxFlow = 0;
        while (findPath()) incFlow();

        cout << sum - maxFlow << endl;

        findPath();
        int cnt = 0;
        FOR(i,1,n) if (tr[i] >= 0) ++cnt;
        cout << cnt << endl;
        FOR(i,1,n) if (tr[i] >= 0) cout << i << ' '; cout << endl;

        cnt = 0;
        FOR(i,1,m) if (tr[n+i] < 0) ++cnt;
        cout << cnt << endl;
        FOR(i,1,m) if (tr[n+i] < 0) cout << i << ' '; cout << endl;
    }
    return 0;
}
