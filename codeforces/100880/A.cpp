
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
#define double long double
using namespace std;

struct Matrix {
    double x[2][2];
} I;

Matrix operator * (const Matrix& a, const Matrix& b) {
    Matrix res;
    REP(i,2) REP(j,2) {
        res.x[i][j] = 0.0;
        REP(k,2) res.x[i][j] += a.x[i][k] * b.x[k][j];
    }
    return res;
}
Matrix power(Matrix a, int k) {
    Matrix res = I;
    while (k > 0) {
        if (k & 1) res = res * a;
        a = a * a;
        k >>= 1;
    }
    return res;
}

double win_white, win_black, lose_white, lose_black;
int n;

double getLose(int n) {
    // after 1 game
    double f[2] = {lose_white, 1.0 - lose_white};

    // transition matrix
    double x, y;
    x = max(lose_white, lose_black);
    y = min(lose_white, lose_black);

    assert(x >= y - 1e-9);
    Matrix T;
    T.x[0][0] = x;     T.x[0][1] = y;
    T.x[1][0] = 1 - x; T.x[1][1] = 1 - y;

    T = power(T, n - 1);
    return T.x[0][0] * f[0] + T.x[0][1] * f[1];
}

double solve() {
    if (n == 1) {
        // only 1 game --> want to win immediately
        return win_white;
    }

    double p_lose = getLose(n-1);
    double p_win = 1 - p_lose;

    return p_lose * max(win_white, win_black)
        + p_win * min(win_white, win_black);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    I.x[0][0] = I.x[1][1] = 1;

    FOR(test,1,ntest) {
        cin >> n;
        cin >> win_white >> win_black >> lose_white >> lose_black;
        cout << "Case #" << test << ": " << solve() << endl;
    }
}
