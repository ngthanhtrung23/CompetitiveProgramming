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

vector< pair<int,int > > ke[MN];
int sz[MN], father[MN];

void dfs(int u, int fu = -1) {
    father[u] = fu;
    sz[u] = 1;
    REP(i,ke[u].size()) {
        int v = ke[u][i].first;
        if (v == fu) continue;

        dfs(v, u);
        sz[u] += sz[v];
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int test; cin >> test;
    while (test--) {
        int n;
        cin >> n;
        FOR(i,1,n) ke[i].clear();
        FOR(i,2,n) {
            int u, v, c; cin >> u >> v >> c;
            ++u; ++v;
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));
        }
        dfs(1);

        long long sum = 0;
        FOR(u,1,n)
            REP(i,ke[u].size()) {
                int v = ke[u][i].first;
                if (u == father[v]) {
                    sum += ke[u][i].second * (long long) sz[v] * (n - sz[v]);
                }
            }
        cout << (fixed) << setprecision(9) << sum / (n * (long long) (n-1) / (double) 2) << endl;
    }
    return 0;
}
