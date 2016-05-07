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
    return sqrt(max(0.0,x));
}
int GI(int& x) {
    return scanf("%lld", &x);
}

char a[22][22];

bool has(int n, int k) {
    // ver
    FOR(i,1,10) FOR(j,1,10) {
        if (a[i][j] == '*'
                && a[i-1][j] != '*' && a[i-1][j-1] != '*' && a[i-1][j+1] != '*'
                && a[i+k][j] != '*' && a[i+k][j-1] != '*' && a[i+k][j+1] != '*') {
            bool good = 1;
            REP(t,k) {
                if (a[i+t][j] != '*') good = 0;
                if (a[i+t][j-1] == '*') good = 0;
                if (a[i+t][j+1] == '*') good = 0;
            }
            if (!good) continue;

            --n;
            REP(t,k) {
                a[i+t][j] = '0';
            }
        }
    }
    // hor
    FOR(i,1,10) FOR(j,1,10) {
        if (a[i][j] == '*'
                && a[i][j-1] != '*' && a[i-1][j-1] != '*' && a[i+1][j-1] != '*'
                && a[i][j+k] != '*' && a[i-1][j+k] != '*' && a[i+1][j+k] != '*') {
            bool good = 1;
            REP(t,k) {
                if (a[i][j+t] != '*') good = 0;
                if (a[i-1][j+t] == '*') good = 0;
                if (a[i+1][j+t] == '*') good = 0;
            }
            if (!good) continue;

            --n;
            REP(t,k) a[i][j+t] = '0';
        }
    }
    return n == 0;
}

bool empty() {
    FOR(i,1,10) FOR(j,1,10) if (a[i][j] != '0') return 0;
    return 1;
}

bool check() {
    if (!has(1, 4)) return 0;
    if (!has(2, 3)) return 0;
    if (!has(3, 2)) return 0;
    if (!has(4, 1)) return 0;

    return empty();
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("sea.in", "r", stdin);
    freopen("sea.out", "w", stdout);
    int ntest; cin >> ntest;
    while (ntest--) {
        memset(a, ' ', sizeof a);
        FOR(i,1,10) FOR(j,1,10) {
            while (a[i][j] != '*' && a[i][j] != '0')
                cin >> a[i][j];
        }

        cout << (check() ? "YES" : "NO") << endl;
    }
}
