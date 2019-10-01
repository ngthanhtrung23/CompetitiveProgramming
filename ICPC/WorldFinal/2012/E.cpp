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

int n;
bitset<80> ke[80];

bool solve1() {
    REP(a,n) {
        if (ke[a].count() == n) {
            cout << 1 << ' ' << a+1 << endl;
            return true;
        }
    }
    return false;
}
bool solve2() {
    REP(a,n) FOR(b,a+1,n-1) {
        if ((ke[a] | ke[b]).count() == n) {
            cout << 2 << ' ' << a+1 << ' ' << b+1 << endl;
            return true;
        }
    }
    return false;
}
bool solve3() {
    REP(a,n) FOR(b,a+1,n-1) FOR(c,b+1,n-1) {
        if ((ke[a] | ke[b] | ke[c]).count() == n) {
            cout << 3 << ' ' << a+1 << ' ' << b+1 << ' ' << c+1 << endl;
            return true;
        }
    }
    return false;
}
bool solve4() {
    REP(a,n) FOR(b,a+1,n-1) FOR(c,b+1,n-1) FOR(d,c+1,n-1) {
        if ((ke[a] | ke[b] | ke[c] | ke[d]).count() == n) {
            cout << 4 << ' ' << a+1 << ' ' << b+1 << ' ' << c+1 << ' ' << d+1 << endl;
            return true;
        }
    }
    return false;
}
bool solve5() {
    REP(a,n) FOR(b,a+1,n-1) FOR(c,b+1,n-1) FOR(d,c+1,n-1) FOR(e,d+1,n-1) {
        if ((ke[a] | ke[b] | ke[c] | ke[d] | ke[e]).count() == n) {
            cout << 5 << ' ' << a+1 << ' ' << b+1 << ' ' << c+1 << ' ' << d+1 << ' ' << e+1 << endl;
            return true;
        }
    }
    return false;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int test = 0;
    while (cin >> n) {
        REP(i,n) {
            ke[i].reset();
            ke[i].set(i);
        }
        REP(i,n) REP(j,n) {
            char c; cin >> c;
            if (c == '1') ke[i].set(j);
        }
        cout << "Case " << ++test << ": ";
        if (solve1()) continue;
        if (solve2()) continue;
        if (solve3()) continue;
        if (solve4()) continue;
        solve5();
    }
}
