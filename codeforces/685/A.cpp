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

int ndigit(int n) {
    if (n == 0) return 1;
    int res = 0;
    while (n > 0) {
        ++res;
        n /= 7;
    }
    return res;
}

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (S & TWO(X))

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n, m;
    while (cin >> n >> m) {
        int l = ndigit(n-1) + ndigit(m-1);
        if (l > 7) {
            cout << 0 << endl;
            continue;
        }
        int res = 0;
        REP(i,n) REP(j,m) {
            bool ok = true;
            int has = 0;

            int u = i;
            REP(turn,ndigit(n-1)) {
                if (CONTAIN(has,u%7)) ok = false;
                has |= TWO(u % 7);
                u /= 7;
            }

            u = j;
            REP(turn,ndigit(m-1)) {
                if (CONTAIN(has,u%7)) ok = false;
                has |= TWO(u % 7);
                u /= 7;
            }

            if (ok) ++res;
        }
        cout << res << endl;
    }
}
