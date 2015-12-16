
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

int a[4][30];
int n, k;

ll f[30][3][8];

int getBit(int mask, int u) {
    return (mask >> u) & 1;
}
int setBit(int mask, int u, int val) {
    mask -= getBit(mask, u) << u;
    mask += val << u;
    return mask;
}

int main() {
    while (scanf("%d%d", &n, &k) == 2) {
        memset(a, 0, sizeof a);
        while (k--) {
            int x, y, t;
            scanf("%d.%d %d.%d", &x, &t, &y, &t);
            ++x;
            swap(x, y);
            a[x][y] = 1;
        }
//        REP(i,3) {
//            FOR(j,1,n) cout << a[i][j];
//            cout << endl;
//        }
        memset(f, 0, sizeof f);
        f[0][2][7] = 1;
        FOR(col,0,n) FOR(row,0,2) REP(mask,8)
            if (f[col][row][mask]) {
                ll cur = f[col][row][mask];
                int col2 = col;
                int row2 = row + 1;
                if (row2 == 3) {
                    row2 = 0;
                    col2++;
                }
                if (a[row2][col2]) {
                    if (getBit(mask, row2) == 1) {
                        f[col2][row2][setBit(mask, row2, 1)] += cur;
                    }
                }
                else {
                    // put 1*1
                    if (getBit(mask, row2) == 1) {
                        f[col2][row2][setBit(mask, row2, 1)] += cur;
                    }
                    // put 2*1 (vertical)
                    if (row2 > 0 && getBit(mask, row2) == 1
                            && getBit(mask, row2-1) == 0) {
                        int newMask = setBit(mask, row2-1, 1);
                        newMask = setBit(newMask, row2, 1);
                        f[col2][row2][newMask] += cur;
                    }
                    // put 1*2 (hor)
                    if (getBit(mask, row2) == 0) {
                        f[col2][row2][setBit(mask, row2, 1)] += cur;
                    }
                    // do nothing
                    if (getBit(mask, row2) == 1) {
                        f[col2][row2][setBit(mask, row2, 0)] += cur;
                    }
                }
            }
        cout << f[n][2][7] << endl;
    }
}
