
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 111;

#define next __next
int a[MN], b[MN], n, k, c[MN], inv[MN], next[MN];

#define NO { cout << "NO" << endl; return ; }
#define YES { cout << "YES" << endl; return ; }

void solve() {
    bool isIdentity = true;
    FOR(i,1,n) if (b[i] != i) isIdentity = false;
    if (isIdentity) NO;

    FOR(i,1,n) c[i] = i;
    FOR(i,1,n) inv[a[i]] = c[i];
//    PR(inv, n);

    bool aEqualInverse = true;
    bool aEqualB = true;

    FOR(i,1,n) {
        if (a[i] != b[i]) aEqualB = false;
        if (a[i] != inv[i]) aEqualInverse = false;
    }

    if (aEqualInverse && aEqualB) {
        if (k == 1) YES
        else NO;
    }

    FOR(i,1,k) {
        FOR(i,1,n) next[i] = c[a[i]];
        FOR(i,1,n) c[i] = next[i];

        bool cEqualB = true;
        FOR(i,1,n) if (c[i] != b[i]) cEqualB = false;
        if (cEqualB) {
            if ((k - i) % 2 == 0) YES
        }
    }

    FOR(i,1,n) c[i] = i;
    FOR(i,1,k) {
        FOR(i,1,n) next[i] = c[inv[i]];
        FOR(i,1,n) c[i] = next[i];

        bool cEqualB = true;
        FOR(i,1,n) if (c[i] != b[i]) cEqualB = false;

        if (cEqualB) {
            if ((k - i) % 2 == 0) YES
        }
    }
    NO;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) cin >> b[i];

        solve();
    }
    return 0;
}

