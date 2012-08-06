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
const int MN = 5011;

int n0, n1, n2;
long double x[MN], y[MN], z[MN];

int main() {
    ios :: sync_with_stdio(false);
    cin >> n0; FOR(i,1,n0) cin >> x[i];
    cin >> n1; FOR(i,1,n1) cin >> y[i];
    cin >> n2; FOR(i,1,n2) cin >> z[i];

    long double A, B; cin >> A >> B;

    long double r1 = x[1];
    FOR(i,2,n0) r1 = max(r1, x[i]);

    long double p1;
    long double p2 = z[1];
    FOR(i,2,n2) p2 = min(p2, z[i]);

    long double res = 0.0;
    FOR(i,1,n1) {
        p1 = y[i];
        long double now = B * p1 * r1 * r1;
        now = now / (A*p2 + B*p1);
        now = sqrt(now);

        res = max(res, now);
    }
    cout << (fixed) << setprecision(10) << res << endl;
    return 0;
}
