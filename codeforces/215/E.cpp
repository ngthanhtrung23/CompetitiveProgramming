#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

ll mult(ll x, int period, int k) {
    ll res = 0;
    while (k--) {
        res = (res << (ll)period) + x;
    }
    return res;
}

#define TWO(x) (1LL<<(x))

ll get(ll gh) {
    if (gh == 0) return 0;
    if (gh == 1) return 0;

    int len = 0;
    ll u = gh;
    while (u) {
        ++len;
        u /= 2;
    }

    long long sum = 0;
    FOR(period,1,len-1)
    FOR(k,2,len)
    if (k * period <= len) {
        long long l = 0, r = TWO(period) - 1, res = 0;
        while (l <= r) {
            long long mid = (l + r) >> 1;
            if (mult(mid, period, k) <= gh) {
                res = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }

        ll add = res - get(res);

        if (period > 1) {
            if (res <= TWO(period-1) - 1) continue;
            add -= TWO(period-1) - 1;
            add += get(TWO(period-1) - 1);
        }

        sum += add;
//        cout << gh << ' ' << period << ' ' << k << ' ' << add << endl;
    }
    return sum;
}

int main() {
    ll l, r;
    while (cin >> l >> r) {
        cout << get(r) - get(l-1) << endl;
    }
    return 0;
}
