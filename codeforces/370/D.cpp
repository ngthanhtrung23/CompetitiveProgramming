
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 2011;
int sum[MN][MN];
int m, n, white;
char tmp[MN], a[MN][MN];

int get(int u, int v, int x, int y) {
    if (u > x || v > y) return 0;
    return sum[x][y] - sum[u-1][y] - sum[x][v-1] + sum[u-1][v-1];
}

int min_size = MN;
int save_up, save_down, save_left, save_right;

bool check(int up, int down, int left, int right) {
    return get(up, left, down, right) - get(up+1, left+1, down-1, right-1) == white;
}

void solve(int min_row, int max_row, int min_col, int max_col, int t1, int t2, int t3, int t4) {
    int up_from = t1 ? min_row : 1;
    int up_to   = t1 ? min_row : min_row;

    int down_from = t2 ? max_row : max_row;
    int down_to   = t2 ? max_row : m;

    int left_from = t3 ? min_col : 1;
    int left_to   = t3 ? min_col : min_col;

    int right_from = t4 ? max_col : max_col;
    int right_to   = t4 ? max_col : n;


    FOR(up, up_from, up_to)
        FOR(down, down_from, down_to)
        FOR(left, left_from, left_to)
        FOR(right, right_from, right_to) {
            if (down - up != right - left) continue;

            int sz = down - up;
            if (sz >= min_size) continue;

            if (check(up, down, left, right)) {
                min_size = sz;
                save_up = up;
                save_down = down;
                save_left = left;
                save_right = right;
            }
        }
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d\n", &m, &n) == 2) {
        white = 0;
        min_size = MN;
        int min_row, max_row, min_col, max_col;
        FOR(i,1,m) {
            gets(tmp);
            FOR(j,1,n) {
                sum[i][j] = sum[i-1][j] + sum[i][j-1] - sum[i-1][j-1];
                a[i][j] = tmp[j-1];
                if (tmp[j-1] == 'w') {
                    ++sum[i][j];
                    white++;

                    if (white == 1) {
                        min_row = max_row = i;
                        min_col = max_col = j;
                    }
                    else {
                        min_row = min(min_row, i);
                        max_row = max(max_row, i);

                        min_col = min(min_col, j);
                        max_col = max(max_col, j);
                    }
                }
            }
        }
        solve(min_row, max_row, min_col, max_col, 1, 1, 0, 0);
        solve(min_row, max_row, min_col, max_col, 1, 0, 1, 0);
        solve(min_row, max_row, min_col, max_col, 1, 0, 0, 1);

        solve(min_row, max_row, min_col, max_col, 0, 1, 1, 0);
        solve(min_row, max_row, min_col, max_col, 0, 1, 0, 1);
        solve(min_row, max_row, min_col, max_col, 0, 0, 1, 1);

        if (min_size == MN) {
            cout << -1 << endl;
        }
        else {
            FOR(i,1,m) {
                FOR(j,1,n) {
                    if (a[i][j] == 'w') putchar('w');
                    else {
                        if ((i == save_up || i == save_down) && save_left <= j && j <= save_right) putchar('+');
                        else if ((j == save_left || j == save_right) && save_up <= i && i <= save_down) putchar('+');
                        else putchar('.');
                    }
                }
                puts("");
            }
        }
    }
    return 0;
}
