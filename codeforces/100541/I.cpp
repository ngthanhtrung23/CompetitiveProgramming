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

const int MN = 1011;

int m, n;
int a[MN][MN], f1[MN][MN], f2[MN][MN], f3[MN][MN], f4[MN][MN];
char tmp[MN];

int main() {
    int ntest; scanf("%d", &ntest);
    assert(0 < ntest && ntest <= 20);
    while (ntest--) {
        scanf("%d%d\n", &m, &n);
        assert(1 <= m && m <= 1000);
        assert(1 <= n && n <= 1000);
        FOR(i,1,m) {
            gets(tmp);
            int l = strlen(tmp);
            assert(l == n);

            REP(j,n) {
                assert(tmp[j] == '0' || tmp[j] == '1');
                a[i][j+1] = tmp[j] - '0';
            }
        }

        memset(f1, 0, sizeof f1);
        memset(f2, 0, sizeof f2);
        memset(f3, 0, sizeof f3);
        memset(f4, 0, sizeof f4);
        // Calculate f1
        FOR(i,1,m) FOR(j,1,n) if (a[i][j]) {
            f1[i][j] = 1;
            if (a[i-1][j]) {
                f1[i][j] = 2 + f1[i-1][j-1];
            }
        }
        // Calculate f2
        FOR(i,1,m) FOR(j,1,n) if (a[i][j]) {
            f2[i][j] = 1;
            if (a[i][j+1]) {
                f2[i][j] = 2 + f2[i-1][j+1];
            }
        }
        // Calculate f3
        FORD(i,m,1) FORD(j,n,1) if (a[i][j]) {
            f3[i][j] = 1;
            if (a[i+1][j]) {
                f3[i][j] = 2 + f3[i+1][j+1];
            }
        }
        // Calculate f4
        FORD(i,m,1) FORD(j,n,1) if (a[i][j]) {
            f4[i][j] = 1;
            if (a[i][j-1]) {
                f4[i][j] = 2 + f4[i+1][j-1];
            }
        }
        int res = 0;
        FOR(i,1,m) FOR(j,1,n) if (a[i][j]) {
            res = max(res, 1 + f1[i][j-1] + f2[i-1][j] + f3[i][j+1] + f4[i+1][j]);
        }
        cout << res << "\n";
    }
    return 0;
}
