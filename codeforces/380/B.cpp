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

const int MN = 7011;
int n, q;
int l[MN], r[MN], t[MN], x[MN], mark[1000111], p2[1000111];
vector<int> res;

void add(int x) {
    if (!mark[x]) {
        mark[x] = 1;
        res.push_back(x);
    }
}

void reset() {
    for(int x : res) {
        mark[x] = 0;
    }
    res.clear();
}

void init() {
    memset(p2, 0, sizeof p2);
    for(int i = 1; i < 1000111; i *= 2)
        p2[i] = 1;
    for(int i = 1; i < 1000111; ++i)
        p2[i] = p2[i-1] + p2[i];
}

int from[MN], to[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> q) {
        init();
        int k = 0;
        FOR(i,1,q) {
            int typ; cin >> typ;
            if (typ == 1) {
                ++k;
                cin >> t[k] >> l[k] >> r[k] >> x[k];
            }
            else {
                int level, v; cin >> level >> v;
                memset(from, 0, sizeof from);
                memset(to, 0, sizeof to);
                from[level] = to[level] = v;
                FOR(i,level+1,n) {
                    from[i] = from[i-1] + p2[from[i-1] - 1];
                    to[i] = to[i-1] + p2[to[i-1]];
                }
                FOR(i,1,k) {
                    if (to[t[i]] < l[i] || r[i] < from[t[i]]) continue;
                    add(x[i]);
                }
                cout << res.size() << "\n";
                reset();
            }
        }
    }
    return 0;
}
