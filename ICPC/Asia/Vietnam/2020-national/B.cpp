#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)

int n_row, n_col;
vector<string> board;

bool inside(int u, int v) {
    return 0 <= u && u < n_row
        && 0 <= v && v < n_col;
}

int solve() {
    deque< pair<int,int> > qu;
    vector< vector<int> > dist(n_row, vector<int> (n_col, -1));

    auto add = [&qu, &dist] (int u, int v, int cur_dist) {
        assert(inside(u, v));

        if (board[u][v] == '#') {
            qu.push_front({u, v});
            dist[u][v] = cur_dist;
        } else {
            assert(board[u][v] == '.');
            qu.push_back({u, v});
            dist[u][v] = cur_dist + 1;
        }
    };

    // Add initial verties
    for (int i = 0; i < n_row; i++) {
        if (board[i][0] != '@') {
            add(i, 0, 0);
        }
    }

    for (int j = 0; j < n_col; j++) {
        if (board.back()[j] != '@') {
            add(n_row - 1, j, 0);
        }
    }

    while (!qu.empty()) {
        auto [u, v] = qu.front(); qu.pop_front();
        if (u == 0 || v == n_col - 1) {
            return dist[u][v];
        }

        FOR(di,-1,1) FOR(dj,-1,1) if (di || dj) {
            int uu = u + di;
            int vv = v + dj;
            if (inside(uu, vv) && board[uu][vv] != '@' && dist[uu][vv] < 0) {
                add(uu, vv, dist[u][v]);
            }
        }
    }
    return -1;
}

int32_t main() {
    ios::sync_with_stdio(0);
    while (cin >> n_row >> n_col && n_row && n_col) {
        board.resize(n_row);
        for (auto& row : board) {
            cin >> row;
            assert(row.size() == n_col);
        }

        cout << solve() << '\n';
    }
}
