#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

long long n, m, i, j, a, b;
const long long oo = 1000111000111000LL;

long long go(long long i, long long j, long long u, long long v) {
    if (i == u && j == v) return 0;
    if (i - a < 1 && i + a > n) return oo;
    if (j - b < 1 && j + b > m) return oo;
    if (llabs(i - u) % a) return oo;
    if (llabs(j - v) % b) return oo;
    long long x = llabs(i - u) / a, y = llabs(j - v) / b;
    if ((x + y) % 2) return oo;
    return max(x, y);
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> m >> i >> j >> a >> b) {
        long long res = min(
                min(go(i, j, 1, 1), go(i, j, n, m)),
                min(go(i, j, 1, m), go(i, j, n, 1)));

        if (res == oo) cout << "Poor Inna and pony!";
        else cout << res;
        cout << endl;
    }
    return 0;
}

