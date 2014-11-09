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

const int MN = 100111;
long long len[MN];
pair<int,int> q[MN];
int m;
map<long long, int> cache;

int get(long long u) {
    if (cache.count(u)) return cache[u];
    int i = lower_bound(len+1, len+m+1, u) - len;
    if (q[i].second == 0) return cache[u] = q[i].first;
    else {
        int x = (u - len[i-1]) % q[i].first;
        if (x == 0) x = q[i].first;
        return cache[u] = get(x);
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m) {
        cache.clear();
        len[0] = 0;
        FOR(i,1,m) {
            int typ; cin >> typ;
            if (typ == 1) {
                int u; cin >> u;
                q[i] = make_pair(u, 0);
                len[i] = len[i-1] + 1;
            }
            else {
                int l, c; cin >> l >> c;
                q[i] = make_pair(l, c);
                len[i] = len[i-1] + l * (long long) c;
            }
        }
        int q; cin >> q;
        while (q--) {
            long long u; cin >> u;
            cout << get(u) << ' ';
        }
        cout << endl;
    }
    return 0;
}
