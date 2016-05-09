
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

int cnt[1000111], n, a[10111];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n;
        FOR(i,1,n) {
            cin >> a[i];
            cnt[a[i]]++;
        }
        sort(a+1, a+n+1);
        n = unique(a+1, a+n+1) - a - 1;

        int res = 0;
        FOR(i,1,n) {
            int u = a[i];
            res += cnt[u] * (cnt[u] - 1LL) / 2;

            for(int v = u+u; v <= 1000000; v += u)
                res += cnt[u] * cnt[v];
        }
        cout << res << '\n';

        FOR(i,1,n) cnt[a[i]] = 0;
    }
}
