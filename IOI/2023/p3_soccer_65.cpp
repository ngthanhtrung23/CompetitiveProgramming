// 65.5
// Solution: https://www.facebook.com/code.cung.rr/posts/pfbid02T9vTA4HW5agdWtXaeiLwnrvucM67wjb8E6547Yu2CYqz4kScPM2bowLo5y69XYZ9l

#include <bits/stdc++.h>
#include "soccer.h"
using namespace std;

struct Row {
    int first, last;
    int cnt() const {
        return last - first + 1;
    }
    bool contains(const Row& b) const {
        return first <= b.first && b.last <= last;
    }
    bool operator < (const Row& b) const {
        return cnt() > b.cnt();
    }
};

pair<bool, int> subtask_25p(int n, const vector<vector<int>>& forest) {
    int cnt_row = 0; // number of non-empty rows
    int first_row = n, last_row = -1;
    int total = 0;
    vector<Row> rows;

    for (int r = 0; r < n; ++r) {
        int cnt = 0; // number of empty cells
        int first = n, last = -1; // all empty cells should be in [first, last]
        for (int c = 0; c < n; ++c) {
            if (forest[r][c] == 0) {
                ++total; ++cnt;
                if (first == n) first = c;
                last = c;
            }
        }
        if (cnt == 0) continue; // ignore empty rows

        if (first_row == n) first_row = r;
        last_row = r;
        ++cnt_row;

        // Condition: in each row, there should be only 1 sequence of 0
        if (cnt != last - first + 1) return {false, -1};

        rows.push_back(Row{first, last});
    }

    // Condition: all rows with empty cells must be consecutive
    if (cnt_row != last_row - first_row + 1) return {false, -2};

    // From biggest row, each row should contains the row next to (& further away from) it
    int largest_row = min_element(rows.begin(), rows.end()) - rows.begin();
    for (int i = largest_row; i > 0; --i) {
        if (!rows[i].contains(rows[i-1])) return {false, -3};
    }
    for (int i = largest_row; i + 1 < (int) rows.size(); ++i) {
        if (!rows[i].contains(rows[i+1])) return {false, -4};
    }

    // In decreasing order of size, row should contains next row
    sort(rows.begin(), rows.end());
    for (int i = 0; i + 1 < (int) rows.size(); ++i) {
        if (!rows[i].contains(rows[i+1])) return {false, -5};
    }
    return {true, total};
}

int dp[33][33][33][33];
void upMax(int& f, int val) {
    if (val > f) f = val;
}

int sub4(int n, vector<vector<int>> forest) {
    for (int i = 0; i < n; ++i) {
        std::partial_sum(forest[i].begin(), forest[i].end(), forest[i].begin());
    }
    auto get_sum = [&] (int row, int l, int r) { // [l, r]
        return forest[row][r] - (l == 0 ? 0 : forest[row][l-1]);
    };

    memset(dp, -1, sizeof dp);
    int res = 0;
    for (int first_row = n-1; first_row >= 0; --first_row) {
        for (int last_row = first_row; last_row < n; ++last_row) {
            // base case: only 1 row
            if (first_row == last_row) {
                for (int l = 0; l < n; ++l) {
                    for (int r = l; r < n; ++r) {
                        if (get_sum(first_row, l, r) == 0) {
                            dp[first_row][first_row][l][r] = r - l + 1;
                        }
                    }
                }
            }
            
            for (int l = 0; l < n; ++l) {
                for (int r = l; r < n; ++r) {
                    int cur = dp[first_row][last_row][l][r];
                    if (cur < 0) continue;
                    res = max(res, cur);

                    for (int l2 = l; l2 <= r; l2++) {
                        for (int r2 = l2; r2 <= r; r2++) {
                            // update: add 1 row above
                            if (first_row > 0 && get_sum(first_row - 1, l2, r2) == 0) {
                                upMax(dp[first_row - 1][last_row][l2][r2], cur + r2 - l2 + 1);
                            }
                            // update: add 1 row below
                            if (last_row + 1 < n && get_sum(last_row + 1, l2, r2) == 0) {
                                upMax(dp[first_row][last_row + 1][l2][r2], cur + r2 - l2 + 1);
                            }
                        }
                    }
                }
            }
        }
    }
    return res;
}

int sub1(int n, const vector<vector<int>>& forest) {
    for (int r = 0; r < n; ++r) {
        for (int c = 0; c < n; ++c) {
            if (forest[r][c] == 1) {
                return n * n - min({
                    (r+1) * (c+1),
                    (r+1) * (n-c),
                    (n-r) * (c+1),
                    (n-r) * (n-c),
                });
            }
        }
    }
    return n*n;
}

int biggest_stadium(int n, vector<vector<int>> forest) {
    auto [is_good, cnt] = subtask_25p(n, forest);
    if (is_good) return cnt;
    if (n <= 30) return sub4(n, forest);
    return sub1(n, forest);
}
