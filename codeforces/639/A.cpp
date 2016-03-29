
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

const int MN = 300111;
int n, k, q, a[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (scanf("%lld%lld%lld", &n, &k, &q) == 3) {
        FOR(i,1,n) scanf("%lld", &a[i]);
        set<int> all;

        FOR(i,1,q) {
            int typ, id; scanf("%lld%lld", &typ, &id);
            if (typ == 1) {
                all.insert(a[id]);
                if (SZ(all) > k) all.erase(all.begin());
            }
            else {
                cout << (all.count(a[id]) ? "YES" : "NO") << endl;
            }
        }
    }
}
