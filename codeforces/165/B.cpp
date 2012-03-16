#include <iomanip>
#include <sstream>
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
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

ll n;
int k;

bool check(ll v) {
    ll cur = 1, can = 0;
    while (cur <= v) {
        can += v / cur;
        if (can >= n) return true;
        cur *= k;
    }
    if (can >= n) return true;
    return false;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    cin >> n >> k;
    ll l = 0, r = n * k, res = r;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (check(mid)) {
            res = mid;
            r = mid - 1;
        }
        else l = mid + 1;
    }
    cout << res;
    return 0;
}
