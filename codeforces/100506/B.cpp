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

const int MN = 10111;
vector<int> ke[MN];
int d[MN], id[MN];
int important[MN];
int a[MN];
int save[211][MN];

void bfs(int u) {
    memset(d, -1, sizeof d);
    queue<int> qu; qu.push(u);
    d[u] = 0;
    while (!qu.empty()) {
        u = qu.front(); qu.pop();
        REP(i,ke[u].size()) {
            int v = ke[u][i];
            if (d[v] < 0) {
                qu.push(v);
                d[v] = d[u] + 1;
            }
        }
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int test; cin >> test;
    while (test--) {
        int nz, nr;
        cin >> nz >> nr;

        FOR(i,1,9999) ke[i].clear();
        memset(important, false, sizeof important);

        FOR(i,1,nz) {
            cin >> id[i];
            int k; cin >> k;
            while (k--) {
                int u; cin >> u;
                ke[id[i]].push_back(u);
            }
        }
        FOR(i,1,nr) {
            int k; cin >> k;
            while (k--) {
                int u; cin >> u;
                important[u] = true;
            }
        }
        int cnt = 0;
        FOR(i,1,9999)
            if (important[i]) {
                a[++cnt] = i;
            }
        FOR(i,1,cnt) {
            bfs(a[i]);
            FOR(x,1,nz)
                save[i][x] = d[id[x]];
        }
        int res = 1000111, u = -1;
        FOR(j,1,nz) {
            int cur = 0;
            FOR(i,1,cnt)
                cur = max(cur, save[i][j]);
            if (cur < res || (cur == res && id[j] < id[u])) {
                res = cur;
                u = j;
            }
        }
        cout << 1 + res << ' ' << id[u] << endl;
    }
    return 0;
}
