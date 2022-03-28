#include "bits/stdc++.h"

enum class Cell { POINT, OBSTACLE, EMPTY };
std::ostream& operator << (std::ostream& out, const Cell& c) {
    switch (c) {
        case Cell::POINT:
            out << 'o';
            return out;
        case Cell::OBSTACLE:
            out << 'X';
            return out;
        case Cell::EMPTY:
            out << '.';
            return out;
        default:
            out << '?';
            return out;
    }
}

const std::vector< std::pair<int,int> > DIRS = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
};

struct Solution {
    int n_row, n_col;
    std::vector<std::vector<Cell>> board;

    bool inside(int r, int c) {
        return 0 <= r && r < n_row
            && 0 <= c && c < n_col;
    }

    std::vector<std::vector<std::pair<int,int>>> trace;
    std::vector<std::pair<int,int>> points;

    void dfs(int u, int v) {
        if (board[u][v] == Cell::POINT) {
            points.push_back({u, v});
        }

        for (auto [di, dj] : DIRS) {
            int uu = u + di, vv = v + dj;
            if (!inside(uu, vv)) continue;
            if (board[uu][vv] == Cell::OBSTACLE) continue;
            if (trace[uu][vv].first >= 0) continue;

            trace[uu][vv] = {u, v};
            dfs(uu, vv);
        }
    }

    void solve() {
        // read input
        std::cin >> n_row >> n_col;
        board = std::vector<std::vector<Cell>> (n_row, std::vector<Cell> (n_col, Cell::EMPTY));
        for (int i = 0; i < n_row; i++) {
            std::string s; std::cin >> s;
            for (int j = 0; j < n_col; j++) {
                if (s[j] == '#') board[i][j] = Cell::OBSTACLE;
                else if (s[j] == 'X') board[i][j] = Cell::POINT;
            }
        }

        trace = std::vector<std::vector<std::pair<int,int>>> (n_row, std::vector<std::pair<int,int>> (n_col, {-1, -1}));
        std::vector<std::vector<std::pair<int,int>>> paths;

        // for each region, find points
        for (int i = 0; i < n_row; i++) {
            for (int j = 0; j < n_col; j++) {
                if (board[i][j] == Cell::POINT && trace[i][j].first < 0) {
                    points.clear();
                    trace[i][j] = {i, j};
                    dfs(i, j);

                    int cnt = points.size();
                    if (cnt % 2) {
                        std::cout << -1 << '\n';
                        return;
                    }

                    std::set< std::pair<int,int> > used;

                    std::reverse(points.begin(), points.end());
                    for (auto point : points) {
                        // ignore matched points
                        if (used.count(point)) continue;

                        std::vector< std::pair<int,int> > path;
                        auto [u, v] = point;
                        do {
                            path.push_back({u, v});
                            auto [uu, vv] = trace[u][v];
                            u = uu;
                            v = vv;
                        } while (used.count({u, v}) || board[u][v] != Cell::POINT);
                        used.insert({u, v});

                        path.push_back({u, v});
                        for (int i = 0; i < -1 + (int) path.size(); i++) {
                            paths.push_back({path[i], path[i+1]});
                        }
                    }
                }
            }
        }
        std::cout << paths.size() << '\n';
        for (auto path : paths) {
            assert(!path.empty());

            std::cout << path[0].first+1 << ' ' << path[0].second+1 << ' ';
            std::string dirs = "";
            for (int i = 1; i < (int) path.size(); i++) {
                if (path[i].first == path[i-1].first - 1) dirs += 'U';
                else if (path[i].first == path[i-1].first + 1) dirs += 'D';
                else if (path[i].second == path[i-1].second - 1) dirs += 'L';
                else if (path[i].second == path[i-1].second + 1) dirs += 'R';
            }
            std::cout << dirs << '\n';
        }
    }
};

int main() {
    std::ios::sync_with_stdio(0); std::cin.tie(0);
    int ntest; std::cin >> ntest;
    Solution s;
    while (ntest--) {
        s.solve();
    }
}
