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

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n, m;
    while (scanf("%lld%lld", &n, &m) == 2) {
        set<int> all;
        FOR(i,1,n) {
            int a; scanf("%lld", &a);
            all.insert(a);
        }

        vector<int> res;
        FOR(i,1,1000000) {
            if (!all.count(i)) {
                if (m < i) break;

                res.push_back(i);
                m -= i;
            }
        }
        printf("%lld\n", SZ(res));
        for(int x : res) printf("%lld ", x);
        puts("");
    }
}
