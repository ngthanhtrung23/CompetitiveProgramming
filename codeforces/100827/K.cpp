
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

bool usedRow[7][7], usedCol[7][7];
char a[11][11];
int n, res[11][11];

bool isResult() {
    return
        res[1][1] == 1 && res[1][2] == 5 && res[1][3] == 2 && res[1][4] == 4 && res[1][5] == 3 &&
        res[2][1] == 2 && res[2][2] == 3 && res[2][3] == 5 && res[2][4] == 1 && res[2][5] == 4 &&
        res[3][1] == 4 && res[3][2] == 2 && res[3][3] == 1 && res[3][4] == 3 && res[3][5] == 5 &&
        res[4][1] == 5 && res[4][2] == 4 && res[4][3] == 3 && res[4][4] == 2;
}

bool check() {
    // look right
    FOR(i,1,n) {
        if (a[i][0] == '-') continue;

        int last = 0, cnt = 0;
        FOR(j,1,n) {
            if (res[i][j] > last) {
                ++cnt;
                last = res[i][j];
            }
        }
        if (cnt + '0' != a[i][0]) return false;
    }
    // look left
    FOR(i,1,n) {
        if (a[i][n+1] == '-') continue;

        int last = 0, cnt = 0;
        FORD(j,n,1) {
            if (res[i][j] > last) {
                ++cnt;
                last = res[i][j];
            }
        }
        if (cnt + '0' != a[i][n+1]) return false;
    }
    // look down
    FOR(j,1,n) {
        if (a[0][j] == '-') continue;

        int last = 0, cnt = 0;
        FOR(i,1,n) {
            if (res[i][j] > last) {
                ++cnt;
                last = res[i][j];
            }
        }
        if (cnt + '0' != a[0][j]) return false;
    }
    // look up
    FOR(j,1,n) {
        if (a[n+1][j] == '-') continue;

        int last = 0, cnt = 0;
        FORD(i,n,1) {
            if (res[i][j] > last) {
                ++cnt;
                last = res[i][j];
            }
        }
        if (cnt + '0' != a[n+1][j]) return false;
    }
    return true;
}

void attempt(int i, int j) {
    if (i > n) {
        if (!check()) return ;
        FOR(u,1,n) {
            FOR(v,1,n) cout << res[u][v];
            cout << '\n';
        }
        throw 1;
    }

    int ii = i, jj = j + 1;
    if (jj > n) {
        ++ii;
        jj = 1;
    }

    FOR(val,1,n)
    if (!usedRow[i][val] && !usedCol[j][val]) {
        if (a[i][j] != '-') {
            if (val + '0' != a[i][j]) continue;
        }
        usedRow[i][val] = true;
        usedCol[j][val] = true;
        res[i][j] = val;

        attempt(ii, jj);

        usedRow[i][val] = false;
        usedCol[j][val] = false;
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n;
        FOR(i,0,n+1) FOR(j,0,n+1) cin >> a[i][j];
        memset(usedRow, 0, sizeof usedRow);
        memset(usedCol, 0, sizeof usedCol);

        try {
            attempt(1, 1);
            cout << "no" << '\n';
        } catch (int e) {
        }
        cout << '\n';
    }
}
