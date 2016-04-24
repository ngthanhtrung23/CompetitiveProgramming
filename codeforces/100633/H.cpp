
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

int GI(int& x) {
    return scanf("%lld", &x);
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n, a, b;
    while (cin >> n >> a >> b) {
        if (a == b) {
            cout << -1 << endl;
            continue;
        }
        if (a > b) {
            a = n - a + 1;
            b = n - b + 1;
        }
        if (b - a == 1 && a != 1 && b != n) {
            cout << -1 << endl;
            continue;
        }
        int res = 0;
        if (a > 1) {
            ++res;
            n -= a;
            b -= a;
            a = 1;
        }
        if (b < n) {
            ++res;
            n = b - 1;
            b = n;
        }
        if (n % 2 == 0) res += (n / 6) * 2 + 1;
        else res += (n + 3) / 6 * 2;
        cout << res << endl;
    }
}
