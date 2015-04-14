
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

int m, n, k, t;
int a[1011];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n >> k >> t) {
        FOR(i,1,k) {
            int u, v; cin >> u >> v; --u; --v;
            a[i] = u * n + v;
        }

        FOR(i,1,t) {
            int res = 0;
            int u, v; cin >> u >> v; --u; --v;
            int cur = u * n + v;

            int cnt = 0;
            FOR(j,1,k) {
                if (cur == a[j]) {
                    res = -1;
                    break;
                }
                else if (cur > a[j]) ++cnt;
            }

            if (res < 0) puts("Waste");
            else {
                cur -= cnt;
                if (cur % 3 == 0) puts("Carrots");
                else if (cur % 3 == 1) puts("Kiwis");
                else puts("Grapes");
            }
        }
    }
    return 0;
}
