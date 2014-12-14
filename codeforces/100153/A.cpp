#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int n;
long double a, b;
long double p[111], q[111], s[111];
long double has[111];
long double res, bestGroup, bestInd[111];

long double get(long double x) {
    long double cur = x * b;
    FOR(i,1,n) has[i] = x * s[i];
    FOR(i,1,n) cur += max( p[i] - has[i], (long double) 0.0 )  / (long double) q[i] * a;

    if (cur < res) {
        res = cur;
        bestGroup = x;
        FOR(i,1,n) bestInd[i] = max( (p[i] - has[i]), (long double) 0.0 ) / (long double) q[i];
    }
    return cur;
}

long double ternary(long double l, long double r) {
    REP(turn,100) {
        long double x1 = (l + l + r) / 3.0;
        long double x2 = (l + r + r) / 3.0;
        long double f1 = get(x1), f2 = get(x2);

        if (f1 < f2) r = x2;
        else l = x1;
    }
}

int main() {
    freopen("academy.in", "r", stdin);
    freopen("academy.out", "w", stdout);
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(16);
    while (cin >> n >> a >> b) {
        FOR(i,1,n) cin >> p[i] >> q[i] >> s[i];
        res = 1e20;
        ternary(0, 1000);
        for(long double x = 0.0; x <= 1000; x += 1) {
            get(x);
            min(res, ternary(x, x+1));
        }
        cout << res << endl;
        cout << bestGroup << endl;
        FOR(i,1,n) cout << bestInd[i] << ' '; cout << endl;
    }
    return 0;
}

