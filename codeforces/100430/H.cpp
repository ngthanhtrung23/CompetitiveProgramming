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

const int MN = 200111;

int n, a[MN];
bool visited[MN];

int cur[MN], nCur;
int res[MN], go[MN];

void solve() {
    FOR(i,1,n) if (a[i] == i) {
        cout << -1 << endl;
        return ;
    }
    memset(res, 0, sizeof res);
    memset(visited, false, sizeof visited);
    FOR(i,1,n) if (!visited[i]) {
        nCur = 1; cur[1] = i;
        int u = a[i];
        while (u != i) {
            cur[++nCur] = u;
            u = a[u];
        }

        FOR(i,1,nCur) visited[cur[i]] = true;

        // PR(cur, nCur);

        FOR(t,1,nCur) {
            int u = cur[t];
            if (a[u] > u) {
                res[u*2] = u*2;
                go[u] = u*2-1;
            } else {
                res[u*2-1] = u*2-1;
                go[u] = u*2;
            }
        }
        FOR(t,1,nCur) {
            int u = cur[t];
            res[go[u]] = go[a[u]];
        }
    }
    FOR(i,1,n+n) cout << res[i] << ' '; cout << endl;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("restore.in", "r", stdin);
    freopen("restore.out", "w", stdout);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        solve();
    }
    return 0;
}
