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

const int MN = 6011;
int n, a[MN], res;
vector<int> ke[MN];
vector<int> d;

void dfs(int u, int fu) {
    auto it = lower_bound(d.begin(), d.end(), a[u]);
    int save = *it;
    *it = a[u];

    res = max(res, (int) (it - d.begin()) + 1);

    for(int v : ke[u]) {
        if (v == fu) continue;
        dfs(v, u);
    }

    *it = save;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,n-1) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        res = 0;
        FOR(i,1,n) {
            d = vector<int> (n+1, 1000111000);
            dfs(i, -1);
        }
        cout << res << endl;
    }
    return 0;
}
