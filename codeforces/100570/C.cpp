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

const int MN = 411;

int m, n, q;
int lg[MN], a[MN][MN];
int nn[10][10][MN][MN], ln[10][10][MN][MN];

void init() {
    for(int i = 1, t = 0; i < MN; i *= 2, ++t)
        lg[i] = t;
    FOR(i,2,MN-1)
        if (!lg[i])
            lg[i] = lg[i-1];
}

void initRMQ() {
    FOR(ti,0,9) FOR(tj,0,9) if (ti || tj) {
        FOR(i,1,m-(1<<ti)+1) FOR(j,1,n-(1<<tj)+1) {
            if (ti == 0) {
                nn[ti][tj][i][j] = min(nn[ti][tj-1][i][j], nn[ti][tj-1][i][j + (1<<(tj-1))]);
                ln[ti][tj][i][j] = max(ln[ti][tj-1][i][j], ln[ti][tj-1][i][j + (1<<(tj-1))]);
            }
            else {
                nn[ti][tj][i][j] = min(nn[ti-1][tj][i][j], nn[ti-1][tj][i + (1<<(ti-1))][j]);
                ln[ti][tj][i][j] = max(ln[ti-1][tj][i][j], ln[ti-1][tj][i + (1<<(ti-1))][j]);
            }
        }
    }
}

int getDiff(int top, int left, int bottom, int right) {
    int ti = lg[bottom - top + 1], tj = lg[right - left + 1];
    int maxVal = max(
            max(ln[ti][tj][top][left], ln[ti][tj][top][right - (1<<tj) + 1]),
            max(ln[ti][tj][bottom - (1<<ti) + 1][left], ln[ti][tj][bottom - (1<<ti) + 1][right - (1<<tj) + 1]));
    int minVal = min(
            min(nn[ti][tj][top][left], nn[ti][tj][top][right - (1<<tj) + 1]),
            min(nn[ti][tj][bottom - (1<<ti) + 1][left], nn[ti][tj][bottom - (1<<ti) + 1][right - (1<<tj) + 1]));
    return maxVal - minVal;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    init();
    while (cin >> m >> n >> q) {
        FOR(i,1,m) FOR(j,1,n) {
            cin >> a[i][j];
            nn[0][0][i][j] = ln[0][0][i][j] = a[i][j];
        }
        initRMQ();
        
        while (q--) {
            int k; cin >> k;
            long long res = 0;
            FOR(top,1,m) FOR(bottom,top,m) {
                int j = 1;
                FOR(i,1,n) {
                    while (j <= i && getDiff(top, j, bottom,i) > k) ++j;
                    if (i >= j) res += i - j + 1;
                }
            }
            cout << res << "\n";
        }
    }
    return 0;
}
