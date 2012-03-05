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
using namespace std;

const double PI = acos(-1.0);

pair<ll,ll> a[100111];

ll gcd(ll x, ll y) {
    if (!y) return x;
    return gcd(y, x % y);
}

ll line(ll a, ll b) {
    if (a < 0) a = - a;
    if (b < 0) b = - b;
    if (a == 0) return b;
    else if (b == 0) return a;
    return gcd(a, b);
}

int n;

ll get() {
    ll s = 0;
    ll B = 0, I = 0;
    a[n+1] = a[1];
    FOR(i,1,n) B += line(a[i+1].F - a[i].F, a[i+1].S - a[i].S);
    FOR(i,1,n) s += (a[i+1].F - a[i].F) * (a[i+1].S + a[i].S);
    if (s < 0) s = -s;
    I = (s + 2 - B) / 2;
//    cout << "2s = " << s << endl;
//    cout << "B = " << B << endl;
//    cout << "I = " << I << endl;
    return B + I;
}

int main() {
    freopen("semi-cool.in", "r", stdin);
    freopen("semi-cool.out", "w", stdout);
    while (scanf("%d", &n) == 1) {
        int x, y;
        FOR(i,1,n) {
            scanf("%d%d", &x, &y);
            a[i] = MP(x, y);
        }
        ll c0 = get();
        FOR(i,1,n) a[i].F <<= 1;
        ll c1 = get();
        FOR(i,1,n) a[i].S <<= 1;
        ll c2 = get();
        FOR(i,1,n) a[i].F >>= 1;
        ll c3 = get();
        cout << c2 - c3 - c1 + c0 << endl;
    }
    return 0;
}
