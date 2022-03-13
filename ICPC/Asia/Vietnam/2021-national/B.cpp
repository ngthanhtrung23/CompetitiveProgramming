#include <bits/stdc++.h>

int dist(char a, char b) {
    if (a > b) std::swap(a, b);

    // a <= b
    return std::min(b - a, 'Z' - b + 1 + a - 'A');
}

int min_dist(std::vector<char> cells) {
    int res = 1e9;
    for (char c = 'A'; c <= 'Z'; c++) {
        int cur_dist = 0;
        for (char cell : cells) {
            cur_dist += dist(cell, c);
        }
        res = std::min(res, cur_dist);
    }
    return res;
}

int main() {
    // read input
    int n_row, n_col;
    std::cin >> n_row >> n_col;

    std::vector<std::string> board(n_row);
    for (auto& row : board) std::cin >> row;

    int res = 0;
    // for each cell, find all its reflections
    for (int i1 = 0, i2 = n_row - 1; i1 <= i2; i1++, i2--) {
        for (int j1 = 0, j2 = n_col - 1; j1 <= j2; j1++, j2--) {
            std::set<std::pair<int,int>> cells {
                {i1, j1},
                {i1, j2},
                {i2, j1},
                {i2, j2}};

            std::vector<char> cell_vals;
            std::transform(cells.begin(), cells.end(), std::back_inserter(cell_vals),
                    [board] (auto ij) { return board[ij.first][ij.second]; });

            res += min_dist(cell_vals);
        }
    }
    std::cout << res << std::endl;
}
