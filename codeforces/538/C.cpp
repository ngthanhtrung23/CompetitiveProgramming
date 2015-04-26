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

const int MN = 100111;
int n, m, d[MN], h[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &n, &m) == 2) {
        FOR(i,1,m) scanf("%d%d", &d[i], &h[i]);

        bool can = true;
        int res = *max_element(h+1, h+m+1);

        res = max(res, h[1] + d[1] - 1);
        res = max(res, h[m] + n - d[m]);

        FOR(i,1,m-1) {
            int d1 = d[i], d2 = d[i+1];
            int h1 = h[i], h2 = h[i+1];
            if (h1 > h2) swap(h1, h2);

            // h1 <= h2
            if (d2 - d1 < h2 - h1) {
                can = false;
                break;
            }
            else {
                d1 += h2 - h1;
                res = max(res, h2 + (d2 - d1) / 2);
            }
        }

        if (!can) cout << "IMPOSSIBLE" << endl;
        else cout << res << endl;
    }
    return 0;
}
