#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 200111;

int n, m;
long long a[MN], b[MN], c[MN], aright[MN], bright[MN], aleft[MN], bleft[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        int k = 0;
        FOR(i,1,n) {
            cin >> a[i];
            c[++k] = a[i];
        }
        FOR(i,1,m) {
            cin >> b[i];
            c[++k] = b[i];
        }
        sort(a+1, a+n+1);
        sort(b+1, b+m+1);
        sort(c+1, c+k+1);
        k = unique(c+1, c+k+1) - c - 1;
        // PR(c, k);
        // PR(a, n);
        // PR(b, m);

        memset(aright, 0, sizeof aright);
        memset(bright, 0, sizeof bright);
        memset(aleft, 0, sizeof aleft);
        memset(bleft, 0, sizeof bleft);

        FORD(i,n,1) aright[i] = aright[i+1] + a[i];
        FORD(i,m,1) bright[i] = bright[i+1] + b[i];

        FOR(i,1,n) aleft[i] = aleft[i-1] + a[i];
        FOR(i,1,m) bleft[i] = bleft[i-1] + b[i];

        long long res = 1000111000111000111LL;
        if (b[m] <= a[1]) res = 0;

        FOR(t,1,k) {
            // DEBUG(c[t]);
            long long cur = 0;
            // a[i] >= c[t]
            if (a[n] < c[t]) {
                cur += c[t] * n - aleft[n];
            }
            else if (a[1] < c[t]) {
                int i = lower_bound(a+1, a+n+1, c[t]) - a;
                cur += c[t] * (i-1) - aleft[i-1];
            }
            // DEBUG(cur);

            // b[i] <= c[t]
            if (b[1] > c[t]) {
                cur += bleft[m] - c[t] * m;
            }
            else if (b[m] > c[t]) {
                int i = upper_bound(b+1, b+m+1, c[t]) - b;
                cur += bright[i] - c[t] * (m-i+1);
            }

            // DEBUG(cur);

            res = min(res, cur);
        }

        cout << res << endl;
    }
    return 0;
}
