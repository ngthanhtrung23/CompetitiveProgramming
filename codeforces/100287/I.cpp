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

int n, m, qu[33];
bool visited[33];
vector<int> ke[33];

vector<int> bfs() {
    memset(visited, false, sizeof visited);
    vector<int> res;
    FOR(i,1,n) if (!visited[i]) {
        int first = 1, last = 1; qu[1] = i; visited[i] = true;
        while (first <= last) {
            int u = qu[first++];
            for(int v : ke[u]) {
                if (!visited[v]) {
                    visited[v] = true;
                    qu[++last] = v;
                }
            }
        }
        res.push_back(last);
    }
    return res;
}

map< vector<int>, double > f;

double get(vector<int> cur) {
    if (f.count(cur)) return f[cur];
    if (cur.size() == 1) return f[cur] = 0.0;

    int ways = n * (n-1) / 2;
    int badWays = 0;
    REP(i,cur.size()) badWays += cur[i] * (cur[i] - 1) / 2;

    double res = 0.0;
    FOR(i,0,cur.size()-1) FOR(j,i+1,cur.size()-1) {
        vector<int> next = cur;
        next[i] += next[j];
        next[j] = next.back();
        next.pop_back();
        sort(next.begin(), next.end());

        res += cur[i] * cur[j] / (double) ways * (get(next) + 1);
    }
    res += badWays / (double) ways;
    return f[cur] = res / (1 - badWays / (double) ways);
}

int main() {
    freopen("interconnect.in", "r", stdin); freopen("interconnect.out", "w", stdout);
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> m) {
        FOR(i,1,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            ke[u].push_back(v);
            ke[v].push_back(u);
        }
        vector<int> cur = bfs();
        // PR0(cur, cur.size());
        
        f.clear();
        cout << get(cur) << endl;
    }
    return 0;
}
