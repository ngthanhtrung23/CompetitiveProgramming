
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

const int MN = 100111;
int n, k, need[MN], has[MN];

bool check(int x) {
    int magic = 0;
    FOR(i,1,n) {
        int can = has[i] / need[i];
        int add = x - can;
        if (add > 3 + k / need[i]) return 0;

        int cur = need[i] * x;
        if (has[i] < cur) magic += cur - has[i];
    }
    return magic <= k;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1 && GI(k) == 1) {
        FOR(i,1,n) GI(need[i]);
        FOR(i,1,n) GI(has[i]);

        int l = 0, r = 3000111000LL, res = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) res = mid, l = mid + 1;
            else r = mid - 1;
        }
        cout << res << endl;
    }
}
