#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cassert>
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define SZ(x) ((int)(x).size())

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

int bfs(const vector<string>& board) {
    int r = SZ(board);
    if (r == 1) return 1;

    int c = SZ(board[0]);
    vector<vector<int> > dist(r, vector<int> (c, -1));
    queue<pair<int,int> > qu;

    assert(board[0][0] == 'G');
    qu.push({0, 0});
    dist[0][0] = 0;

    while (!qu.empty()) {
        int u = qu.front().first;
        int v = qu.front().second;
        qu.pop();

        for (int di = -1; di <= 1; di++)
            for (int dj = -1; dj <= 1; dj++)
                if (di*di + dj*dj <= 1) {
                    int u2 = u + di;
                    int v2 = (v + dj + c) % c;
                    if (u2 < 0) continue;
                    assert(u2 < r);
                    if (board[u2][v2] == 'M') continue;

                    int u3 = u2;
                    int v3 = (v2 - 1 + c) % c;
                    if (board[u3][v3] == 'M') continue;
                    if (dist[u3][v3] >= 0) continue;

                    dist[u3][v3] = dist[u][v] + 1;
                    qu.push({u3, v3});
                    if (u3 == r - 1) {
                        return dist[u3][v3] + 1;
                    }
                }
    }
    return -1;
}

int32_t main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int r, c; cin >> r >> c;
    vector<string> board(r);
    for (auto& s : board) cin >> s;

    cout << bfs(board) << endl;
    return 0;
}
