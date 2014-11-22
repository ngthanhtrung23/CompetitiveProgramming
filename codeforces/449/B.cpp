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

const int MN = 100111;

int n, m, k;
long long f[MN];
vector< pair<int,int> > ke[MN];
int vao[MN];
pair<int,int> trains[MN];

void addEdge(int u, int v, int c) {
    ke[u].push_back(make_pair(v, c));
    ke[v].push_back(make_pair(u, c));
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m >> k) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v, c; cin >> u >> v >> c;
            addEdge(u, v, c);
        }
        FOR(i,1,k) {
            int u, c; cin >> u >> c;
            trains[i] = make_pair(u, c);
            addEdge(1, u, c);
        }

        FOR(i,1,n) f[i] = 1000111000111000LL;
        set< pair<long long, int> > s;
        f[1] = 0; s.insert(make_pair(0LL, 1));
        memset(vao, 0, sizeof vao);

        while (!s.empty()) {
            auto it = *s.begin();
            s.erase(s.begin());
            int u = it.second;
            long long l = it.first;
            if (l != f[u]) continue;

            for(auto e : ke[u]) {
                int v = e.first;
                if (f[v] > f[u] + e.second) {
                    f[v] = f[u] + e.second;
                    vao[v] = 1;
                    s.insert(make_pair(f[v], v));
                }
                else if (f[v] == f[u] + e.second) {
                    vao[v] += 1;
                }
            }
        }
        // PR(f, n);
        // PR(vao, n);

        int res = 0;
        FOR(i,1,k) {
            int u = trains[i].first, c = trains[i].second;

            if (f[u] == c && vao[u] > 1) {
                vao[u] -= 1;
                ++res;
            }
            else if (f[u] < c) ++res;
            // cout << u << ' ' << c << ' ' << res << endl;
        }
        cout << res << endl;
    }
    return 0;
}
