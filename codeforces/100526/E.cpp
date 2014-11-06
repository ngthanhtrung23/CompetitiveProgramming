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

struct Score {
    int x, y, z;
} a[MN];
int n, bit[MN];

#define _(X) ((X) & (-(X)))

int get(int u) {
    int res = MN;
    while (u > 0) {
        res = min(res, bit[u]);
        u -= _(u);
    }
    return res;
}

void update(int u, int val) {
    while (u < MN) {
        bit[u] = min(bit[u], val);
        u += _(u);
    }
}

bool operator < (const Score &a, const Score&b) {
    return a.x < b.x;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n;
        FOR(i,1,n) cin >> a[i].x >> a[i].y >> a[i].z;
        FOR(i,1,n) bit[i] = MN;

        sort(a+1, a+n+1);
        int res = 0;
        FOR(i,1,n) {
            if (get(a[i].y - 1) < a[i].z) {
            }
            else ++res;
            update(a[i].y, a[i].z);
        }
        cout << res << endl;
    }
    return 0;
}
