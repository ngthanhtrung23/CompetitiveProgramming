
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

string a[22];
int n;

char board[2][11][11];
bool used[22];

void attempt(int boardid, int i) {
    if (boardid == 2) {
        REP(t,2) {
            REP(i,n) {
                REP(j,n) putchar(board[t][i][j]);
                puts("");
            }
            puts("");
        }
        throw 1;
    }

    int boardid2 = boardid;
    int i2 = i + 1;
    if (i2 == n) {
        ++boardid2;
        i2 = 0;
    }

    FOR(cur,1,n+n) if (!used[cur]) {
        bool ok = true;
        REP(j,i)
        if (board[boardid][j][i] != a[cur][j]
                || board[boardid][i][j] != a[cur][j]) {
            ok = false;
            break;
        }
        if (!ok) continue;

        used[cur] = true;
        FOR(j,i,n-1) board[boardid][i][j] = board[boardid][j][i] = a[cur][j];

        attempt(boardid2, i2);

        used[cur] = false;
        FOR(j,i,n-1) board[boardid][i][j] = board[boardid][j][i] = ' ';
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("square.in", "r", stdin);
    freopen("square.out", "w", stdout);

    while (cin >> n) {
        FOR(i,1,n+n) cin >> a[i];

        memset(used, 0, sizeof used);
        memset(board, ' ', sizeof board);
        try {
            attempt(0, 0);
        } catch (int e) {
        }
    }
}
