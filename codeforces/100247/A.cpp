
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

int a[200111][3];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (GI(n) == 1) {
        int m0 = 0, m1 = 0, m2 = 0;
        FOR(i,1,n) {
            GI(a[i][0]);
            GI(a[i][1]);
            GI(a[i][2]);

            sort(a[i], a[i]+3);

            m0 = max(a[i][0], m0);
            m1 = max(a[i][1], m1);
            m2 = max(a[i][2], m2);
        }

        vector<int> res;
        FOR(i,1,n) {
            if (a[i][1] > m0 && a[i][2] > m1) res.push_back(i);
        }
        printf("%lld\n", SZ(res));
        for(auto x : res) printf("%lld ", x); puts("");
    }
}
