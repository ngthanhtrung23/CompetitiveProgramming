#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double)0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

const int MN = 55;
int a[MN][MN], val[MN][MN];
int n;

int getSum(int i1, int j1, int i2, int j2) {
    if (i1 < 1) ++i1;
    if (j1 < 1) ++j1;
    if (i2 > n) --i2;
    if (j2 > n) --j2;

    return a[i2][j2] - a[i1-1][j2] - a[i2][j1-1] + a[i1-1][j1-1];
}
int count(int i1, int j1, int i2, int j2) {
    return (i2 - i1 + 1) * (j2 - j1 + 1);
}
int all(int i1, int j1, int i2, int j2, int val) {
    return getSum(i1, j1, i2, j2) == val * count(i1, j1, i2, j2);
}

bool outside(int u, int v) {
    return u < 1 || u > n || v < 1 || v > n;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) {
            char c; cin >> c;
            a[i][j] = val[i][j] = c - '0';
            a[i][j] = a[i-1][j] + a[i][j-1] - a[i-1][j-1] + a[i][j];
        }
        int sumAll = a[n][n];

        try {
            FOR(i1,1,n) FOR(i2,i1,n) FOR(j1,1,n) FOR(j2,j1,n) {
                if (all(i1, j1, i2, j2, 4)
                        && (outside(i1-1, j1) || all(i1-1, j1, i1-1, j2, 2)) // up
                        && (outside(i1, j1-1) || all(i1, j1-1, i2, j1-1, 2)) // left
                        && (outside(i1, j2+1) || all(i1, j2+1, i2, j2+1, 2)) // right
                        && (outside(i2+1, j1) || all(i2+1, j1, i2+1, j2, 2)) // down
                        && (outside(i1-1, j1-1) || val[i1-1][j1-1] == 1)
                        && (outside(i1-1, j2+1) || val[i1-1][j2+1] == 1)
                        && (outside(i2+1, j1-1) || val[i2+1][j1-1] == 1)
                        && (outside(i2+1, j2+1) || val[i2+1][j2+1] == 1)
                        && getSum(i1-1, j1-1, i2+1, j2+1) == sumAll)
                {
                    throw 1;
                }
            }
            cout << "No" << endl;
        } catch (...) {
            cout << "Yes" << endl;
        }
    }
}
