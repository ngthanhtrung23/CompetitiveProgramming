
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 511;
int m, n;
char a[MN][MN];

int sum[2][MN][MN];

int get(int t, int x1, int y1, int x2, int y2) {
    return sum[t][x2][y2] - sum[t][x2][y1-1] - sum[t][x1-1][y2] + sum[t][x1-1][y1-1];
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        memset(a, ' ', sizeof a);
        FOR(i,1,m) scanf("%s\n", &a[i][1]);

        memset(sum[0], 0, sizeof sum[0]);
        memset(sum[1], 0, sizeof sum[1]);
        FOR(i,1,m) FOR(j,1,n) {
            // hor
            sum[0][i][j] = sum[0][i-1][j] + sum[0][i][j-1] - sum[0][i-1][j-1];
            if (a[i][j] == '.' && a[i][j+1] == '.') ++sum[0][i][j];

            // ver
            sum[1][i][j] = sum[1][i-1][j] + sum[1][i][j-1] - sum[1][i-1][j-1];
            if (a[i][j] == '.' && a[i+1][j] == '.') ++sum[1][i][j];
        }

        int q; scanf("%d", &q);
        while (q--) {
            int x1, y1, x2, y2;
            scanf("%d%d%d%d", &x1, &y1, &x2, &y2);

            int res = 0;
            res += get(0, x1, y1, x2, y2-1);
            res += get(1, x1, y1, x2-1, y2);
            printf("%d\n", res);
        }
    }
}
