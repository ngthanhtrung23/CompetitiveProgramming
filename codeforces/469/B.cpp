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

int good[2011];
pair<int,int> x[1011];

int main() {
    ios :: sync_with_stdio(false);
    int p, q, l, r;
    while (cin >> p >> q >> l >> r) {
        memset(good, false, sizeof good);
        while (p--) {
            int u, v; cin >> u >> v;
            FOR(i,u,v) good[i] = true;
        }

        FOR(i,1,q) cin >> x[i].first >> x[i].second;

        int res = 0;
        FOR(t,l,r) {
            bool can = false;
            FOR(i,1,q) {
                FOR(u,t+x[i].first,t+x[i].second) {
                    if (good[u]) can = true;
                }
                if (can) break;
            }
            if (can) {
                ++res;
            }
        }
        cout << res << endl;
    }
    return 0;
}
