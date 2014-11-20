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
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 300111;
int n, p;
map<int,int> ke[MN];
int deg[MN], actual[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> p) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,n) deg[i] = actual[i] = 0;
        FOR(i,1,n) {
            int u, v; cin >> u >> v;
            ke[u][v] += 1;
            ke[v][u] += 1;
            deg[u]++;
            deg[v]++;
        }
        FOR(i,1,n) actual[i] = deg[i];
        sort(deg+1, deg+n+1);

        long long res = 0;
        FOR(i,1,n) {
            int need = p - actual[i];
            if (deg[1] >= need) {
                res += n-1;
            }
            else if (deg[n] < need) {
            }
            else {
                int id = lower_bound(deg+1, deg+n+1, need) - deg;
                if (actual[i] >= need) ++id;
                res += (n - id + 1);
            }

            for(pair<int,int> cur : ke[i]) {
                int v = cur.first;
                if (actual[v] >= need) --res;

                if (actual[v] + actual[i] - cur.second >= p) ++res;
            }
        }
        cout << res / 2 << endl;
    }
    return 0;
}