#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
long long a[MN], b[MN];
int n;

void solve() {
    long long res = 0;
    FOR(i,1,n) {
        if (b[i] < 2) {
            --res;
            continue;
        }
        if (a[i] + a[i] < b[i]) {
            --res;
            continue;
        }
        long long x = b[i] / 2;
        long long y = b[i] - x;
        res += x * y;
    }
    cout << res << endl;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) cin >> b[i];

        solve();
    }
    return 0;
}

