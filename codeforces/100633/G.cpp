
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

const int MN = 200111;
int a[MN], sum[MN];

int count(int l, int r) {
    return r - l + 1;
}
int getSum(int l, int r) {
    return sum[r] - sum[l-1];
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (GI(n) == 1) {
        int hour = 1e12;
        int minu = 1e6;
        FOR(i,1,n) {
            int h, m, s; GI(h); GI(m); GI(s);
            a[i] = h * hour + m * minu + s;
        }
        sort(a+1, a+n+1);
        FOR(i,n+1,n+n) {
            a[i] = a[i-n] + 12 * hour;
        }
        FOR(i,1,n+n) sum[i] = sum[i-1] + a[i];

        int res = 12 * hour * n;
        FOR(u,1,n) {
            int v = u + n - 1;

            int cur = 0;
            cur += a[v] * count(u, v) - getSum(u, v);

            res = min(res, cur);
        }
        cout << res / hour << ' ' << (res % hour) / minu << ' ' << res % minu << endl;
    }
}
