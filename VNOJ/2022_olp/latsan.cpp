/**
 * Repeat these steps:
 * 1. Ask a random query (x, y)
 * 2. Find cells that can be covered in only 1 way
 * 3. Repeat 2 until no such cells
 */
#include "bits/stdc++.h"
using namespace std;

const vector<pair<int,int>> DIRS = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0},
};

int main() {
    ios::sync_with_stdio(0);
    int n, k; cin >> n >> k;

    vector<vector<int>> a(n*k+1, vector<int> (n*k+1, 0));
    int bar_id = 0;

    auto inside = [&] (int r, int c) {
        return 1 <= r && r <= n*k
            && 1 <= c && c <= n*k;
    };

    auto print = [&] () {
#ifdef ONLINE_JUDGE
        return;
#endif
        cout << "===== board =====" << endl;
        for (int i = 1; i <= n*k; i++) {
            for (int j = 1; j <= n*k; j++) {
                cout << a[i][j] << ' ';
            }
            cout << endl;
        }
    };

    auto all_empty = [&] (int r1, int c1, int r2, int c2) {
        for (int r = r1; r <= r2; r++) {
            for (int c = c1; c <= c2; c++) {
                if (a[r][c]) return false;
            }
        }
        return true;
    };

    auto cnt_possible = [&] (int r, int c, bool fill, set<pair<int,int>>& interestings) -> int {
        int res = 0;
        // vertical
        for (int r1 = r - k + 1; r1 <= r; r1++) {
            int r2 = r1 + k - 1;
            if (!inside(r1, c)) continue;
            if (!inside(r2, c)) continue;

            if (all_empty(r1, c, r2, c)) {
                ++res;
                if (fill) {
                    assert(res == 1);
                    bar_id++;

                    for (int i = r1; i <= r2; i++) {
                        assert(!a[i][c]);
                        a[i][c] = bar_id;

                        for (auto [di, dj] : DIRS) {
                            if (inside(i+di, c+dj) && !a[i+di][c+dj]) {
                                interestings.insert({i+di, c+dj});
                            }
                        }
                    }
                }
            }
        }

        // horizontal
        for (int c1 = c - k + 1; c1 <= c; c1++) {
            int c2 = c1 + k - 1;
            if (!inside(r, c1)) continue;
            if (!inside(r, c2)) continue;

            if (all_empty(r, c1, r, c2)) {
                ++res;
                if (fill) {
                    assert(res == 1);
                    bar_id++;

                    for (int i = c1; i <= c2; i++) {
                        assert(!a[r][i]);
                        a[r][i] = bar_id;

                        for (auto [di, dj] : DIRS) {
                            if (inside(r+di, i+dj) && !a[r+di][i+dj]) {
                                interestings.insert({r+di, i+dj});
                            }
                        }
                    }
                }
            }
        }
        return res;
    };

    auto global_heuristics = [&] (set<pair<int,int>>& interestings) {
        while (!interestings.empty()) {
            set<pair<int,int>> new_interests;
            for (auto [r, c] : interestings) {
                if (a[r][c] == 0) {
                    if (cnt_possible(r, c, false, new_interests) == 1) {
                        cnt_possible(r, c, true, new_interests);
                    }
                }
            }
            interestings = std::move(new_interests);
        }
    };

    auto _set = [&] (int r, int c, int b) {
        a[r][c] = b;
    };

    auto query = [&] (int r, int c) {
        assert(a[r][c] == 0);

        ++bar_id;
        _set(r, c, bar_id);
        cout << "ASK " << r << ' ' << c << endl;

        std::set< std::pair<int,int> > interestings;
        for (auto [di, dj] : DIRS) {
            if (inside(r+di, c+dj)) {
                interestings.insert({r + di, c + dj});
            }
        }

        for (int i = 0; i < k-1; i++) {
            int r2, c2; cin >> r2 >> c2;
            assert(a[r2][c2] == 0);

            _set(r2, c2, bar_id);
            for (auto [di, dj] : DIRS) {
                if (inside(r2+di, c2+dj)) {
                    interestings.insert({r2 + di, c2 + dj});
                }
            }
        }
        global_heuristics(interestings);
    };
    
    for (int row = k; row <= n*k; row += k) {
        for (int col = k; col <= n*k; col += k) {
            if (!a[row][col]) {
                query(row, col);
                print();
            }
        }
    }

    while (bar_id < n*n*k) {
        int row = rand() % (n*k) + 1;
        int col = rand() % (n*k) + 1;
        while (a[row][col]) {
            row = rand() % (n*k) + 1;
            col = rand() % (n*k) + 1;
        }
        query(row, col);
        print();
    }

    cout << "ANSWER" << endl;
    for (int b = 1; b <= bar_id; b++) {
        for (int r = 1; r <= n*k; r++) {
            for (int c = 1; c <= n*k; c++) {
                if (a[r][c] == b) cout << r << ' ' << c << ' ';
            }
        }
        cout << endl;
    }
    return 0;
}
