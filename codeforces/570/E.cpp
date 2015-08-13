
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

const int MOD = 1e9 + 7;
int f[2][511][511];
char a[511][511], tmp[511];
int m, n;

void add(int& x, int val) {
    x += val;
    if (x >= MOD) x -= MOD;
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) {
            gets(tmp);
            FOR(j,1,n) a[i][j] = tmp[j-1];
        }
        memset(f, 0, sizeof f);
        int res = 0;
        FOR(sum1,2,m+n) {
            int jump = sum1 - 2;
            int sum2 = m + n - jump;

            int next = sum1 & 1;
            int cur = 1 - next;

            memset(f[next], 0, sizeof f[next]);
            
            if (sum1 == 2) {
                if (a[1][1] == a[m][n])
                    f[next][1][m] = 1;
            }
            else {
                FOR(i1,1,m) FOR(i2,1,m) if (f[cur][i1][i2]) {
                    int j1 = sum1 - 1 - i1;
                    int j2 = sum2 + 1 - i2;
                    int t = f[cur][i1][i2];

//                    cout << sum1 << ' ' << i1 << ' ' << j1 << "   " << i2 << ' ' << j2 << "   " << t << endl;

                    if (j1 < n) {
                        if (j2 > 1 && a[i1][j1+1] == a[i2][j2-1])
                            add(f[next][i1][i2], t);
                        if (i2 > 1 && a[i1][j1+1] == a[i2-1][j2])
                            add(f[next][i1][i2-1], t);
                    }
                    if (i1 < m) {
                        if (j2 > 1 && a[i1+1][j1] == a[i2][j2-1])
                            add(f[next][i1+1][i2], t);
                        if (i2 > 1 && a[i1+1][j1] == a[i2-1][j2])
                            add(f[next][i1+1][i2-1], t);
                    }
                }
            }

            if (sum1 == sum2) {
                FOR(i,1,m) add(res, f[next][i][i]);
                break;
            }
            else if (sum1 + 1 == sum2) {
                FOR(i1,1,m) FOR(i2,i1,i1+1) {
                    int j1 = sum1 - i1;
                    int j2 = sum2 - i2;

                    if (abs(i1 - i2) + abs(j1 - j2) == 1 && a[i1][j1] == a[i2][j2])
                        add(res, f[next][i1][i2]);
                }
                break;
            }
        }
        cout << res << endl;
    }
}

