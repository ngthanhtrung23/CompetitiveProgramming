#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

void print(int n, const vector<vector<int>>& a) {
    cout << "YES\n";
    FOR(i,1,n) {
        FOR(j,1,n) cout << a[i][j] << ' ';
        cout << '\n';
    }
    cout << endl;
}

// add numbers to a row, where columns in range [from, to]
void add_row(vector<vector<int>>& a, int& cur, int row, int from, int to) {
    if (from <= to) {
        FOR(j,from,to) a[row][j] = ++cur;
    } else {
        FORD(j,from,to) a[row][j] = ++cur;
    }
}

// add numbers to a column, where rows in range [from, to]
void add_col(vector<vector<int>>& a, int& cur, int column, int from, int to) {
    if (from <= to) {
        FOR(i,from,to) a[i][column] = ++cur;
    } else {
        FORD(i,from,to) a[i][column] = ++cur;
    }
}

void solveOdd(int n, int start_row, int start_col) {
    int cur = 0;
    bool flip = false;
    if (start_row == 1) {
        flip = true;
        swap(start_row, start_col);
    }
    bool flip_vertical = false;
    if (start_col == n) {
        flip_vertical = true;
        start_col = n - start_col + 1;
    }

    vector<vector<int>> a(n+1, vector<int> (n+1, 0));


    if (start_row % 2 == 1) {
        add_row(a, cur, start_row, start_col, 1);

        if (start_row > 1) {
            FOR(j,1,start_col) {
                if (j % 2 == 1) {
                    add_col(a, cur, j, start_row-1, 1);
                } else {
                    add_col(a, cur, j, 1, start_row-1);
                }
            }
        }

        if (start_col < n) {
            FOR(i,1,start_row) {
                if (i % 2 == 1) {
                    add_row(a, cur, i, start_col+1, n);
                } else {
                    add_row(a, cur, i, n, start_col+1);
                }
            }
        }
    } else {
        FORD(i,start_row,1) {
            if ((start_row - i) % 2 == 0) {
                add_row(a, cur, i, start_col, 1);
            } else {
                add_row(a, cur, i, 1, start_col);
            }
        }
        if (start_col < n) {
            FOR(j,start_col+1,n) {
                if ((j - start_col) % 2) {
                    add_col(a, cur, j, 1, start_row);
                } else {
                    add_col(a, cur, j, start_row, 1);
                }
            }
        }
    }

    if (start_row < n) {
        FOR(i,start_row+1,n) {
            if ((i - start_row) % 2) {
                add_row(a, cur, i, n, 1);
            } else {
                add_row(a, cur, i, 1, n);
            }
        }
    }

    if (flip_vertical) {
        FOR(i,1,n) {
            reverse(a[i].begin() + 1, a[i].end());
        }
    }
    if (flip) {
        FOR(i,1,n) FOR(j,1,n) {
            if (i < j) swap(a[i][j], a[j][i]);
        }
    }

    print(n, a);
}

void solveEven(int n, int start_row, int start_col) {
    vector<vector<int>> a(n+1, vector<int> (n+1, 0));

    int cur = 0;
    add_col(a, cur, 1, 1, n);
    FORD(row,n,1) {
        if (row % 2 == 0) add_row(a, cur, row, 2, n);
        else add_row(a, cur, row, n, 2);
    }

    int sub = a[start_row][start_col] - 1;
    FOR(i,1,n) FOR(j,1,n) {
        a[i][j] -= sub;
        if (a[i][j] < 1) a[i][j] += n*n;
    }

    print(n, a);
}

int32_t main() {
    ios::sync_with_stdio(0);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n, start_row, start_col;
        cin >> n >> start_row >> start_col;

        if (n % 2 == 1 && (start_row + start_col) % 2 == 1) {
            cout << "NO" << endl;
            continue;
        }

        if (n % 2 == 1) solveOdd(n, start_row, start_col);
        else solveEven(n, start_row, start_col);
    }
    cerr << "\nTime elapsed: " << 1000 * clock() / CLOCKS_PER_SEC << "ms\n";
    return 0;
}

