
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

const int MN = 1011;

int n, each, q, a[MN], sum[MN], need[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> each) {
        FOR(i,1,n) {
            cin >> a[i];
            sum[i] = sum[i-1] + a[i];

            need[i] = (sum[i] % each == 0) ? sum[i] / each : sum[i] / each + 1;
        }
        need[n+1] = 1000111000;
        int q; cin >> q;
        while (q--) {
            int u; cin >> u;
            if (u > need[n]) u = need[n];
            int i = upper_bound(need+1, need+n+2, u) - need - 1;
            printf("%d %d\n", i, each * u - sum[i]);
        }
    }
}
