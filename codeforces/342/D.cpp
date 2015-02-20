
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

const int MOD = 1000000007;

int n;
char a[5][10111];
int f[10111][4][8][2];

void update(int& x, int val) {
    x += val;
    if (x >= MOD) x -= MOD;
}

int main() {
    while (scanf("%d\n", &n) == 1) {
        memset(a, ' ', sizeof a);
        FOR(i,1,3) scanf("%s\n", &a[i][1]);
        memset(f, 0, sizeof f);

        f[1][1][7][0] = 1;
        FOR(j,1,n) FOR(i,1,3) REP(mask,8) REP(good,2)
        if (f[j][i][mask][good]) {
            int ii = i + 1;
            int jj = j;
            if (ii == 4) {
                ++jj;
                ii = 1;
            }
            int cur = f[j][i][mask][good];

            if (a[i][j] == 'O' || a[i][j] == 'X') {
                int x = (mask >> (i-1)) & 1;
                if (x == 1) {
                    update(f[jj][ii][mask][good], cur);
                }
            }
            else {
                // skip
                int x = (mask >> (i-1)) & 1;
                if (x == 1) {
                    update(f[jj][ii][mask - (1<<(i-1))][good], cur);
                }

                // add hor
                x = (mask >> (i-1)) & 1;
                if (x == 0) {
                    int good2 = good;
                    if (a[i][j-2] == 'O' || a[i][j+1] == 'O') good2 = 1;
                    update(f[jj][ii][mask + (1<<(i-1))][good2], cur);
                }

                // add ver
                if (i >= 2) {
                    int x = (mask >> (i-2)) & 1;
                    int y = (mask >> (i-1)) & 1;
                    if (x == 0 && y == 1) {
                        int good2 = good;
                        if (a[i-2][j] == 'O' || a[i+1][j] == 'O') good2 = 1;
                        update(f[jj][ii][mask + (1<<(i-2))][good2], cur);
                    }
                }
            }
        }
        cout << f[n+1][1][7][1] << endl;
    }
    return 0;
}
