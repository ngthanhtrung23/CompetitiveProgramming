
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

int m, n, a[111][111], rows[111], cols[111], flip[111];

void print(const vector<int>& x) {
    memset(flip, 0, sizeof flip);
    for(int t : x) flip[t] = 1 - flip[t];

    int cnt = 0;
    FOR(i,1,100) if (flip[i]) ++cnt;
    printf("%d", cnt);
    FOR(i,1,100) if (flip[i]) printf(" %d", i);
    puts("");
}

int main() {
    while (scanf("%d%d", &m, &n) == 2) {
        FOR(i,1,m) FOR(j,1,n) scanf("%d", &a[i][j]);
        memset(rows, 0, sizeof rows);
        memset(cols, 0, sizeof cols);

        vector<int> res_rows, res_cols;

        FOR(i,1,m) FOR(j,1,n) {
            rows[i] += a[i][j];
            cols[j] += a[i][j];
        }

        while (true) {
            int minRow = *min_element(rows+1, rows+m+1);
            int minCol = *min_element(cols+1, cols+n+1);

            if (minRow >= 0 && minCol >= 0) break;

            if (minRow < minCol) {
                int i = min_element(rows+1, rows+m+1) - rows;
                FOR(j,1,n) {
                    a[i][j] = -a[i][j];
                    rows[i] += 2 * a[i][j];
                    cols[j] += 2 * a[i][j];
                }
                res_rows.push_back(i);
            }
            else {
                int j = min_element(cols+1, cols+n+1) - cols;
                FOR(i,1,m) {
                    a[i][j] = -a[i][j];
                    rows[i] += 2 * a[i][j];
                    cols[j] += 2 * a[i][j];
                }
                res_cols.push_back(j);
            }
        }

        FOR(i,1,m) FOR(j,1,n) {
            rows[i] -= a[i][j];
            cols[j] -= a[i][j];
        }
        FOR(i,1,m) assert(rows[i] == 0);
        FOR(j,1,n) assert(cols[j] == 0);

        print(res_rows);
        print(res_cols);
    }
    return 0;
}

