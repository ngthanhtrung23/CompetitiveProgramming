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

const int MN = 3011;
int a[MN][MN], m, n, f[MN][MN];

void rotate() {
    FOR(i,1,m) FOR(j,1,n) f[i][j] = a[i][j];
    swap(m, n);

    FOR(i,1,m) FOR(j,1,n) a[i][j] = f[j][i];
}

bool can3(int a, int b, int c) {
    return c - b == b - a;
}
bool canRow(int i, int j) {
    return can3(a[i][j], a[i][j+1], a[i][j+2]);
}
bool canCol(int i, int j) {
    return can3(a[i][j], a[i+1][j], a[i+2][j]);
}

int solve1() {
    int res = 1;

    if (n > 1) res = 2;
    else return res;

    FOR(i,1,m) {
        FORD(j,n-1,1) {
            f[i][j] = 2;

            if (j <= n-2 && canRow(i, j)) {
                f[i][j] = f[i][j+1] + 1;
            }
            else f[i][j] = 2;

            res = max(res, f[i][j]);
        }
    }

    return res;
}

int solve2() {
    if (m < 2) return 0;
    if (n < 2) return 0;

    int res = 4;
    FOR(i,1,m-1) {
        FORD(j,n-1,1) {
            f[i][j] = 2;

            if (j <= n-2 && canRow(i, j) && canRow(i+1, j)) {
                f[i][j] = f[i][j+1] + 1;
            }
            else f[i][j] = 2;

            res = max(res, f[i][j] * 2);
        }
    }

    return res;
}

int h[MN], st[MN], l[MN], r[MN];

int maxRect(int m, int n) {
    memset(h, 0, sizeof h);

    int res = 0;
    FOR(i,1,m) {
        FOR(j,1,n) if (f[i][j]) ++h[j]; else h[j] = 0;

        int top = 0; st[0] = 0;
        FOR(j,1,n) {
            while (top && h[st[top]] >= h[j]) --top;
            l[j] = st[top] + 1;
            st[++top] = j;
        }

        top = 0; st[top] = n+1;
        FORD(j,n,1) {
            while (top && h[st[top]] >= h[j]) --top;
            r[j] = st[top] - 1;
            st[++top] = j;
        }

        FOR(j,1,n) {
            if (h[j])
                res = max(res, (h[j] + 2) * (r[j] - l[j] + 3));
        }
    }
    return res;
}

int solve3() {
    if (m < 3) return 0;
    FOR(i,1,m-2) FOR(j,1,n-2) {
        if (canRow(i, j) && canRow(i+1, j) && canRow(i+2, j)
                && canCol(i, j) && canCol(i, j+1) && canCol(i, j+2)) {
            f[i][j] = 1;
        }
        else f[i][j] = 0;
    }
    return maxRect(m-2, n-2);
}

int solve12() {
    return max(solve1(), solve2());
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; scanf("%d", &ntest);
    while (ntest--) {
        scanf("%d%d", &m, &n);
        FOR(i,1,m) FOR(j,1,n) scanf("%d", &a[i][j]);

        int res = solve12();
        res = max(res, solve3());

        rotate();
        res = max(res, solve12());
        printf("%d\n", res);
    }
}
