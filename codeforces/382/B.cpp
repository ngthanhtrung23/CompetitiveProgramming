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

long long a, b, w, x, c;
pair<long long, long long> f[66][1011];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> a >> b >> w >> x >> c) {
        FOR(k,0,w-1) {
            if (k >= x) f[0][k] = make_pair(k-x, 0);
            else f[0][k] = make_pair(w - (x-k), 1);
        }
        FOR(l,1,40) {
            FOR(k,0,w-1) {
                int u = f[l-1][k].first;
                f[l][k] = make_pair( f[l-1][u].first, f[l-1][k].second + f[l-1][u].second );
            }
        }
        long long res = 0;
        while (c > a) {
            long long cur = c - a;

            // cout << c << ' ' << a << ' ' << b << endl;
            res += cur;
            c = c - cur;

            REP(l,40) if (cur & (1LL<<l)) {
                a -= f[l][b].second;
                b = f[l][b].first;
            }
        }
        cout << res << endl;
    }
    return 0;
}
