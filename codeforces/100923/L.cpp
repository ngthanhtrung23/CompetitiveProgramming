
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
    return scanf("%I64d", &x);
}

#define TWO(X) (1LL<<(X))

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("semipal.in", "r", stdin);
    freopen("semipal.out", "w", stdout);

    int ntest; cin >> ntest;
    while (ntest--) {
        int n, k;
        cin >> n >> k;

        --k;

        int half = TWO(n-2);

        char bound = 'a';
        if (k >= half) {
            k -= half;
            bound = 'b';
        }
        cout << bound;
        FORD(i,n-3,0) {
            if ((k >> i) & 1) {
                cout << 'b';
            }
            else cout << 'a';
        }
        cout << bound << endl;
    }
}
