#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
// On CF, GNU C++ seems to have some precision issues with long double?
// #define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define stat akjcjalsjcjalscj
#define hash ajkscjlsjclajsc
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (((S) >> (X)) & 1)

long long rand16() {
    return rand() & (TWO(16) - 1);
}
long long my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(long long& x) { return scanf("%lld", &x); }

string mul(char c, int times) {
    string res = "";
    REP(turn,times) res += c;
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int nRow, nCol, k;
    cin >> nRow >> nCol >> k;
    ++nRow;

    vector<string> board(nRow);
    REP(i,nRow - 1) {
        cin >> board[i];
    }
    board[nRow - 1] = mul('.', nCol);
    vector<int> cost(nCol);
    REP(i,nCol) cin >> cost[i];

    vector<vector<bool>> can(nCol, vector<bool>(nCol, false));
    REP(startCol, nCol) {
        if (board[0][startCol] == 'X') continue;

        queue<pair<int,int>> qu;
        qu.push({0, startCol});
        vector<vector<bool>> visited(nRow, vector<bool>(nCol, false));
        visited[0][startCol] = true;

        while (!qu.empty()) {
            int u = qu.front().first;
            int v = qu.front().second;
            qu.pop();

            if (board[u][v] == 'X') continue;
            function<void(int, int)> visit = [&] (int u, int v) {
                if (u < 0 || u >= nRow || v < 0 || v >= nCol) return;
                if (visited[u][v]) return;
                if (board[u][v] == 'X') return;
                visited[u][v] = true;
                qu.push({u, v});
            };

            if (board[u][v] == '.') {
                visit(u + 1, v);
            }
            if (board[u][v] == 'L') {
                visit(u, v - 1);
            }
            if (board[u][v] == 'R') {
                visit(u, v + 1);
            }
            if (board[u][v] == '?') {
                visit(u, v - 1);
                visit(u, v + 1);
            }
        }

        REP(targetCol, nCol) {
            can[startCol][targetCol] = visited.back()[targetCol];
        }
    }
    vector<vector<int>> f(101, vector<int> (nCol, 0));
    FOR(i,1,100) {
        REP(j,nCol) {
            f[i][j] = -1;

            REP(k,nCol) if (f[i-1][k] >= 0 && can[k][j]) {
                f[i][j] = max(f[i][j], f[i-1][k] + cost[j]);
            }
        }
    }

    if (k <= 100) {
        int res = 0;
        FOR(turn,1,k) res = max(res, *max_element(f[turn].begin(), f[turn].end()));
        cout << res << endl;
    } else {
        int res = 0;
        FOR(turn,1,100) res = max(res, *max_element(f[turn].begin(), f[turn].end()));

        REP(prevCol,nCol) if (f[100][prevCol] >= 0) {
            REP(lastCol, nCol) if (can[prevCol][lastCol] && can[lastCol][lastCol]) {
                res = max(res, (k - 100) * cost[lastCol] + f[100][prevCol]);
            }
        }

        REP(a,nCol) if (f[99][a] >= 0) {
            REP(b,nCol) REP(c,nCol) {
                if (can[a][b] && can[b][b] && can[b][c]) {
                    int na = 99;
                    int nb = k - 100;
                    int nc = 1;
                    res = max(res, f[na][a] + nb * cost[b] + nc * cost[c]);
                }
            }
        }

        cout << res << endl;
    }
    return 0;
}
