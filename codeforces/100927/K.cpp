
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("wheels.in", "r", stdin);
    freopen("wheels.out", "w", stdout);
    int n, m, a, b, t;
    while (cin >> n >> m >> a >> b >> t) {
        if (n > m) {
            swap(n, m);
            swap(a, b);
        }
        
        if (m % n) {
            cout << 0 << endl;
            continue;
        }

        if (m == n && a == b) {
            cout << -1 << endl;
            continue;
        }

        if (m == n) m *= 2;

        cout <<  (t * m * llabs(a - b)) / (a * b) + 1 << endl;
    }
}
