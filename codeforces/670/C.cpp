
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

int n;
int a[200111], b[200111];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        map<int,int> cnt;
        FOR(i,1,n) {
            int a; GI(a);
            cnt[a] += 1;
        }

        int res = 1;
        pair<int,int> best = make_pair(0, 0);

        int q; GI(q);
        FOR(i,1,q) GI(a[i]);
        FOR(i,1,q) GI(b[i]);
        FOR(i,1,q) {
            auto cur = make_pair(cnt[a[i]], cnt[b[i]]);
            if (cur > best) {
                best = cur;
                res = i;
            }
        }
        cout << res << endl;
    }
}
