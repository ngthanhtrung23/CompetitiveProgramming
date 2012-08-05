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
const long long oo = 1000111000111000111LL;

long long check(long long a, long long b, long long c) {
    if (a > b) swap(a, b);
    long long res = a;
    c += a;
    b -= a;
    a -= a;

    if (b % 2 == 1) return oo;
    if (c == 0) return oo;

    res += b;
    return res;
}

int main() {
    long long a, b, c;
    cin >> a >> b >> c;
    long long res = oo;
    res = min(res, check(a, b, c));
    res = min(res, check(b, c, a));
    res = min(res, check(c, a, b));
    if (res == oo) res = -1;
    cout << res << endl;
    return 0;
}
