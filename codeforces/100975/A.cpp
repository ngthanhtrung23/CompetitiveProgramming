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
    return sqrt(max(0.0,x));
}
int GI(int& x) {
    return scanf("%lld", &x);
}

const int MN = 10111;
int n;
pair<int,int> a[MN], b[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("black.in", "r", stdin);
    freopen("black.out", "w", stdout);
    while (GI(n) == 1) {
        FOR(i,1,n) {
            GI(a[i].first);
            a[i].second = i;
        }
        FOR(i,1,n) {
            GI(b[i].first);
            b[i].second = i;
        }
        sort(a+1, a+n+1);
        sort(b+1, b+n+1);
        int res = 0;
        FOR(i,1,n) {
            res += llabs(a[i].first - b[i].first);
        }
        printf("%lld\n", res);
        FOR(i,1,n) {
            printf("%lld %lld\n", a[i].second, b[i].second);
        }
    }
}
