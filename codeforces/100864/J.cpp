
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

const int MN = 211;
char a[MN][MN];
vector<int> rows[MN], cols[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("japanese.in", "r", stdin);
    freopen("japanese.out", "w", stdout);
    int m, n;
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        int maxRow = 0, maxCol = 0;
        FOR(i,1,m) {
            rows[i].clear();
            int j = 1;
            while (j <= n) {
                if (a[i][j] == '.') {
                    ++j;
                }
                else {
                    int to = j;
                    while (to < n && a[i][to+1] == 'X') ++to;
                    rows[i].push_back(to - j + 1);
                    j = to + 1;
                }
            }
            maxRow = max(maxRow, SZ(rows[i]));
            reverse(rows[i].begin(), rows[i].end());
        }
        FOR(j,1,n) {
            cols[j].clear();
            int i = 1;
            while (i <= m) {
                if (a[i][j] == '.') ++i;
                else {
                    int to = i;
                    while (to < m && a[to+1][j] == 'X') ++to;
                    cols[j].push_back(to - i + 1);
                    i = to + 1;
                }
            }
            maxCol = max(maxCol, SZ(cols[j]));
            reverse(cols[j].begin(), cols[j].end());
        }
        FORD(i,maxCol-1,0) {
            REP(j,maxRow) cout << '*';
            FOR(j,1,n) {
                if (SZ(cols[j]) > i) cout << cols[j][i];
                else cout << '_';
            }
            cout << '\n';
        }
        FOR(i,1,m) {
            FORD(j,maxRow-1,0) {
                if (SZ(rows[i]) > j) cout << rows[i][j];
                else cout << '_';
            }
            FOR(j,1,n) cout << '.';
            cout << '\n';
        }
        cout << endl;
    }
}
