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

int n, m, w;
int bit[MN], a[MN], need[MN];

#define _(x) ((x) & (-(x)))

int get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

void update(int u, int val) {
    while (u <= n) {
        bit[u] += val;
        u += _(u);
    }
}

bool check(int val) {
    FOR(i,1,n)
        if (a[i] >= val) need[i] = 0;
        else need[i] = val - a[i];

    memset(bit, 0, sizeof bit);
    long long res = 0;
    FOR(i,1,n) {
        int cur = a[i] + get(i) - get(i-w);
        if (cur < val) {
            update(i, val - cur);
            res += val - cur;
            if (res > m) return false;
        }
    }
    return res <= m;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m >> w) {
        FOR(i,1,n) cin >> a[i];
        int l = 0, r = 1000111000, res = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }
        cout << res << endl;
    }
    return 0;
}
