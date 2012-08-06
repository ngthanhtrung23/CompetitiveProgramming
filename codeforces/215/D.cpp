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

int n, m;
int t, T, x, cost;

long long f(int u) {
    if (T <= t) {
        return cost + m * (ll) x;
    }
    long long res = u * (ll) x;
    if (u) res += cost;
    long long bus = (m - u) / (T - t);
    if ((m-u) % (T-t)) ++bus;

    res += bus * cost;
    return res;
}

long long solve() {
    long long res = 1000111000111LL;
    int l = 0, r = m;
    res = min(res, f(0));
    res = min(res, f(m));

    while (l <= r) {
        if (r - l <= 3) {
            FOR(i,l,r) {
                res = min(res, f(i));
            }
            break;
        }
        int mid1 = (l + l + r) / 3;
        int mid2 = (l + r + r) / 3;
        long long f1 = f(mid1);
        long long f2 = f(mid2);

        if (f1 <= f2) {
            r = mid2;
        }
        else l = mid1;
    }
    return res;
}

int main() {
    while (scanf("%d%d", &n, &m) == 2) {
        long long res = 0;
        FOR(i,1,n) {
            scanf("%d%d%d%d", &t, &T, &x, &cost);
            res += solve();
        }
        cout << res << endl;
    }
    return 0;
}
