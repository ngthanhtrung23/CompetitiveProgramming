
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
int f[MN], n, q, id[MN], a[MN];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> q) {
        FOR(i,1,n) f[i] = n;
        FOR(i,1,n) {
            cin >> a[i];
            id[a[i]] = i;
        }
        while (q--) {
            int x, y; cin >> x >> y;
            x = id[x];
            y = id[y];
            if (x > y) swap(x, y);
            f[x] = min(f[x], y - 1);
        }
        FORD(i,n-1,1) f[i] = min(f[i], f[i+1]);
        int res = 0;
        FOR(i,1,n) res += f[i] - i + 1;
        cout << res << endl;
    }
}
