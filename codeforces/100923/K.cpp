
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

const int MAXT = 1e7 + 3;

int MOD, a, b, x, q;
int pos[MAXT / 100 + 11];

#undef int
int main() {
#define int long long
    freopen("pocnitoare.in", "r", stdin);
    freopen("pocnitoare.out", "w", stdout);

    GI(MOD);
    GI(a);
    GI(b);
    GI(x);
    GI(q);

    int cur = x;
    FOR(i,1,MAXT-1) {
        if (i % 100 == 1) {
            pos[i / 100] = cur;
        }
        cur = (i * cur + a) % MOD;
    }

    int res = 0;
    FOR(i,1,q) {
        int t;
        if (i == 1) {
            GI(t);
        }
        else {
            t = ((i-1) * res + b) % MAXT + 1;
        }
        int tt = t;
        while (tt % 100 != 1) --tt;
        int cur = pos[tt / 100];

        FOR(i,tt,t-1) {
            cur = (i * cur + a) % MOD;
        }

        res = cur;
        printf("%lld\n", res);
    }
}
