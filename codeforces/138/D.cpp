
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

int m, n;
char a[22][22];
int f[2][44][44][44][44];
int mark[5000111];

int main() {
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        memset(f, 0, sizeof f);
        memset(mark, 0, sizeof mark);
        int id = 0;
        REP(t,2) {
            FORD(minSum,m+n,2) FOR(maxSum,minSum,m+n)
                FORD(minDiff,m+n-1,1) FOR(maxDiff,minDiff,m+n-1) {
                    id++;

                    FOR(i,1,maxSum-1)
                    FOR(j,max(1,max(n + i - maxDiff, minSum - i)),min(n, min(n+i-minDiff,maxSum-i))) {
                        if ((i+j) % 2 == t) {
                            if (a[i][j] == 'R') {
                                int diff = i - j + n;
                                int x = f[t][minSum][maxSum][minDiff][diff-1];
                                int y = f[t][minSum][maxSum][diff+1][maxDiff];
                                mark[x^y] = id;
                            }
                            if (a[i][j] == 'L') {
                                int sum = i + j;
                                int x = f[t][minSum][sum-1][minDiff][maxDiff];
                                int y = f[t][sum+1][maxSum][minDiff][maxDiff];
                                mark[x^y] = id;
                            }
                            if (a[i][j] == 'X') {
                                int sum = i+j, diff = i-j+n;
                                int x = f[t][minSum][sum-1][minDiff][diff-1];
                                int y = f[t][minSum][sum-1][diff+1][maxDiff];
                                int z = f[t][sum+1][maxSum][minDiff][diff-1];
                                int w = f[t][sum+1][maxSum][diff+1][maxDiff];

                                mark[x^y^z^w] = id;
                            }
                        }
                    }

                    int res = 0;
                    while (mark[res] == id) ++res;
                    f[t][minSum][maxSum][minDiff][maxDiff] = res;
                }
        }
//        DEBUG(f[0][2][m+n][1][m+n-1]);
//        DEBUG(f[1][2][m+n][1][m+n-1]);
        int res = f[0][2][m+n][1][m+n-1]
                ^ f[1][2][m+n][1][m+n-1];
        if (res) cout << "WIN"; else cout << "LOSE";
        cout << endl;
    }
    return 0;
}
