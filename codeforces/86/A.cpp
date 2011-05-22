#pragma comment(linker, "/STACK:16777216")
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
#include <sstream>
#include <iomanip>

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

ll get(ll u) {
    ll x = 10;
    while (u >= x) x *= 10LL;
    x--;
    return u * (x - u);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    ll u, v; cin >> u >> v;
    ll start = 1;
    ll res = max(get(u), get(v));
    FOR(len,1,9) {
        ll now = 5 * start;
        if (u <= now && now <= v) res = max(res, get(now));
        start *= 10LL;
    }
    cout << res << endl;
    return 0;
}
