#include <bits/stdc++.h>
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
    return sqrt(max(0.0,x));
}

int n, a[3511];
const int ZERO = 15000111;
bitset<ZERO*2> has;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("abc.in", "r", stdin);
    freopen("abc.out", "w", stdout);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            scanf("%d", &a[i]);
            a[i] += ZERO;
        }
        FOR(i,1,n) has.set(a[i]);

        int res = 0;
        FOR(i,1,n) FOR(j,i+1,n) if (a[i] != ZERO && a[j] != ZERO) {
            int cur = a[i] + a[j] - ZERO;
            if (cur >= 0 && cur < ZERO * 2 && has.test(cur)) res += 2;
        }
        cout << res << endl;
    }
}
