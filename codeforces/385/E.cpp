#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

long long MOD;
struct Matrix {
    vector< vector<long long> > x;
    int m, n;

    Matrix(int m = 0, int n = 0) : m(m), n(n) {
        x.resize(m);
        REP(i,m) {
            x[i].resize(n);
            REP(j,n) x[i][j] = 0;
        }
    }
    void print() {
        REP(i,m) {
            REP(j,n) cout << x[i][j] << ' ';
            cout << endl;
        }
    }
};
Matrix operator * (const Matrix &a, const Matrix &b) {
    Matrix c(a.m, b.n);
    REP(i,c.m) REP(j,c.n) {
        REP(k,a.n)
            c.x[i][j] = (c.x[i][j] + a.x[i][k] * b.x[k][j]) % MOD;
    }
    return c;
}

Matrix identity(int n) {
    Matrix res(n, n);
    REP(i,n) res.x[i][i] = 1;
    return res;
}

long long sx, sy, dx, dy, t;
Matrix p[66];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> MOD >> sx >> sy >> dx >> dy >> t) {
        dx %= MOD; dy %= MOD;
        if (dx < 0) dx += MOD;
        if (dy < 0) dy += MOD;
        Matrix A(6, 6);
        A.x = {{2, 1, 1, 0, 1, 0},
               {1, 2, 0, 1, 1, 0},
               {1, 1, 1, 0, 1, 0},
               {1, 1, 0, 1, 1, 0},
               {0, 0, 0, 0, 1, 1},
               {0, 0, 0, 0, 0, 1}};
        Matrix I = identity(6);
        p[0] = A;
        FOR(i,1,63) p[i] = p[i-1] * p[i-1];

        Matrix transform = I;
        REP(i,64)
            if ((t) & (1LL<<i)) {
                transform = transform * p[i];
            }
        
        Matrix start(6, 1);
        start.x = {{(int) (sx % MOD)}, {(int) (sy % MOD)}, {(int) (dx % MOD)}, {(int) (dy % MOD)}, {0}, {1}};

        Matrix end = transform * start;
        int fx = end.x[0][0]; if (fx == 0) fx = MOD;
        int fy = end.x[1][0]; if (fy == 0) fy = MOD;
        cout << fx << ' ' << fy << endl;
    }
    return 0;
}

