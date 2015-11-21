
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
using namespace std;

const int MN = 100111;

int nValue, n, f[MN], a[MN], b[MN], f_rev[MN], cnt[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> nValue >> n) {
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,nValue) {
            cin >> f[i];
            f_rev[f[i]] = i;
            cnt[f[i]] += 1;
        }
        FOR(i,1,n) cin >> b[i];

        bool impossible = false;
        bool ambiguity = false;
        FOR(i,1,n) {
            if (cnt[b[i]] == 0) impossible = true;
            if (cnt[b[i]] > 1) ambiguity = true;
        }
        if (impossible) puts("Impossible");
        else if (ambiguity) puts("Ambiguity");
        else {
            puts("Possible");
            FOR(i,1,n) printf("%d ", f_rev[b[i]]); puts("");
        }
    }
}
