
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

int a[5][5], used[22], b[5][5];
int x[22], row[5], col[5];

bool check(int a[][5]) {
    memset(row, 0, sizeof row);
    memset(col, 0, sizeof col);

    FOR(i,1,4) FOR(j,1,4) {
        row[i] += a[i][j];
        col[j] += a[i][j];
    }

    FOR(i,1,4) if (row[i] != 34 || col[i] != 34) return 0;
    return 1;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        memset(used, 0, sizeof used);
        FOR(i,1,4) FOR(j,1,4) {
            cin >> a[i][j];
            if (a[i][j] > 0) used[a[i][j]] = 1;
        }
        int nx = 0;
        FOR(i,1,16) if (!used[i]) x[++nx] = i;

        cout << "Case " << test << ":\n";
        do {
            int k = 0;
            FOR(i,1,4) FOR(j,1,4) {
                if (a[i][j] < 0) b[i][j] = x[++k];
                else b[i][j] = a[i][j];
            }
            if (check(b)) {
                FOR(i,1,4) {
                    FOR(j,1,4) {
                        cout << b[i][j];
                        if (j == 4) cout << '\n';
                        else cout << ' ';
                    }
                }
                break;
            }
        } while (next_permutation(x+1, x+nx+1));
    }
}
