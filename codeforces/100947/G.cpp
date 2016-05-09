
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

int count(int l, int r) {
    if (l > r) swap(l, r);
    return r - l + 1;
}

int get(int x, int y) {
    if (x == 0 && y == 0) return 0;

    int t = max(llabs(x), llabs(y));
    // 1 --> 8*1
    // 2 --> 8*2
    // ...
    // t-1 --> 8*(t-1)

    int res = 4 * t * (t-1LL);

    if (x == +t && y != -t) {
        return res + count(-(t-1), y);
    }
    else res += 2 * t;

    if (y == +t) {
        return res + count(t-1, x);
    }
    else res += 2 * t;

    if (x == -t) {
        return res += count(t-1, y);
    }
    else res += 2 * t;

    assert(y == -t);
    res += count(-t+1, x);

    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    while (ntest--) {
        int x, y; cin >> x >> y;
        cout << get(x, y) << endl;
    }
}
