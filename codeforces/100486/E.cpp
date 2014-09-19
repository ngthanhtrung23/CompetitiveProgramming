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
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 100111;

int n, m, a, k, d[MN];
vector< pair<int,int> > ke[MN];
int b[MN];

void init() {
    FOR(i,1,n) {
        ke[i].clear();
        d[i] = 1000111000;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m >> a >> k && n) {
        init();
        FOR(i,1,m) {
            int u, v, c; cin >> u >> v >> c;
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));
        }

        set< pair<int,int> > s;

        int res = n;
        FOR(i,1,a) {
            int u; cin >> u;

            if (d[u] >= k) --res;

            s.insert(make_pair(0, u));
            d[u] = 0;

            while (!s.empty()) {
                int u = s.begin()->second, l = s.begin()->first;
                s.erase(s.begin());
                if (l != d[u]) continue;

                REP(i,ke[u].size()) {
                    int v = ke[u][i].first, c = ke[u][i].second;

                    if (d[v] > d[u] + c) {
                        if (d[v] >= k && d[u] + c < k) --res;
                        d[v] = d[u] + c;

                        s.insert(make_pair(d[v], v));
                    }
                }
            }

            // PR(d, n);

            cout << res << endl;
        }

        cout << endl;
    }
    return 0;
}
