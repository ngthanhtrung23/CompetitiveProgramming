#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

int m, n, k, a[111][111];

int fixRow(int u) {
    int res = 0;
    FOR(i,1,m) {
        int same = 0;
        FOR(j,1,n) same += a[i][j] != a[u][j];

        int diff = 0;
        FOR(j,1,n) diff += a[i][j] == a[u][j];

        res += min(same, diff);
    }
    return res;
}

int fixCol(int v) {
    int res = 0;
    FOR(j,1,n) {
        int same = 0;
        FOR(i,1,m) same += a[i][j] != a[i][v];

        int diff = 0;
        FOR(i,1,m) diff += a[i][j] == a[i][v];

        res += min(same, diff);
    }
    return res;
}

int x[111];

int rotate() {
    FOR(i,1,n) x[i] = i;
    do {
        bool ok = true;
        FOR(i,1,m) {
            bool same = true, diff = true;
            FOR(j,1,n) {
                int cur = (j == x[i]) ? (1 - a[i][j]) : a[i][j];
                int ref = (j == x[1]) ? (1 - a[1][j]) : a[1][j];
                if (cur == ref) diff = false;
                else same = false;
            }
            if (!same && !diff) {
                ok = false;
                break;
            }
        }
        if (ok) return m;
    } while (next_permutation(x+1, x+n+1));
    return 1000111000;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n >> k) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        int res = 1000111000;
        FOR(i,1,m) res = min(res, fixRow(i));
        FOR(j,1,n) res = min(res, fixCol(j));

        if (m <= 10 && m == n) {
            res = min(res, rotate());
        }

        cout << ((res > k) ? -1 : res) << endl;
    }
    return 0;
}
