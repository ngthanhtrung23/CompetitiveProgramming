
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
int a[MN], n, bad[MN], nBad;

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        FOR(i,1,n) GI(a[i]);
        nBad = 0;
        FOR(i,1,n) if (a[i] == i) bad[++nBad] = i;
        int res = nBad / 2 + nBad % 2;
        cout << res << '\n';

        if (nBad == 1) {
            FOR(i,1,n) if (i != bad[1] && a[i] != bad[1]) {
                cout << i << ' ' << bad[1] << endl;
                break;
            }
            continue;
        }

        for(int i = 1; i <= nBad; i += 2) {
            int j = i + 1; if (j > nBad) j = i - 1;
            cout << bad[i] << ' ' << bad[j] << '\n';
        }
    }
}
