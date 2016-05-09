
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

const int MN = 2011;
int n, p, q, a[MN], small[MN], big[MN], f[2][MN];

bool check(int w) {
    a[n+1] = 1000111000111000111LL;
    FOR(i,1,n) {
        int j = i;
        while (a[j+1] < a[i] + w) ++j;
        small[i] = j;

        while (a[j+1] < a[i] + w + w) ++j;
        big[i] = j;
    }

    memset(f, 0, sizeof f);
    FOR(i,0,p) {
        int cur = i % 2;
        memset(f[cur], 0, sizeof f[cur]);

        FOR(j,0,q) {
            f[cur][j] = 0;
            if (j) f[cur][j] = max(f[cur][j], big[ f[cur][j-1] + 1 ]);
            if (i) f[cur][j] = max(f[cur][j], small[ f[1-cur][j] + 1 ]);

            if (f[cur][j] >= n) return 1;
        }
    }

    return 0;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> p >> q;
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);

        if (p+q >= n) {
            cout << 1 << '\n';
            continue;
        }

        int l = 1, r = 1000111000;
        int res = r;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        cout << res << '\n';
    }
}
