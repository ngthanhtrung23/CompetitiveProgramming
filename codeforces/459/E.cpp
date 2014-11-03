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

const int MN = 300111;

int n, m;
int f[MN];
vector< pair<int,int> > ls[100111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m) {
        FOR(i,1,100000) ls[i].clear();
        FOR(i,1,m) {
            int u, v, c; cin >> u >> v >> c;
            ls[c].push_back(make_pair(u, v));
        }
        
        memset(f, 0, sizeof f);
        FOR(cost,1,100000) {
            vector< pair<int,int> > updates;
            REP(i,ls[cost].size()) {
                int u = ls[cost][i].first, v = ls[cost][i].second;
                if (f[v] < f[u] + 1) {
                    updates.push_back(make_pair(v, f[u] + 1));
                }
            }
            REP(i,updates.size()) {
                int v = updates[i].first, val = updates[i].second;
                f[v] = max(f[v], val);
            }
        }
        cout << *max_element(f+1, f+n+1) << endl;
    }
    return 0;
}
