
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
int n, p, q, orig[MN], a[MN];

bool check(int turn) {
    int need = 0;
    FOR(i,1,n) {
        a[i] = orig[i] - turn * q;

        if (a[i] <= 0) continue;

        int diff = p - q;
        if (!diff) return 0;

        need += (a[i] + diff - 1) / diff;
    }
    return need <= turn;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        GI(p); GI(q);
        FOR(i,1,n) GI(orig[i]);

        int l = 0, r = 1000111000, res = 1000111000;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) res = mid, r = mid - 1;
            else l = mid + 1;
        }
        cout << res << endl;
    }
}
