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

int GI(int& x) {
    return scanf("%lld", &x);
}

int m, n, q, a[111][111];

struct Q {
    int typ;
    int i, j, val;
} queries[10111];

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(m) == 1 && GI(n) == 1) {
        GI(q);
        FOR(i,1,q) {
            GI(queries[i].typ);
            if (queries[i].typ == 3) {
                GI(queries[i].i);
                GI(queries[i].j);
                GI(queries[i].val);
            }
            else GI(queries[i].i);
        }
        memset(a, 0, sizeof a);
        FORD(i,q,1) {
            if (queries[i].typ == 3) {
                a[ queries[i].i ][ queries[i].j ] = queries[i].val;
            }
            else if (queries[i].typ == 1) {
                int r = queries[i].i;
                int last = a[r][n];
                FORD(i,n,2) a[r][i] = a[r][i-1];
                a[r][1] = last;
            }
            else {
                int c = queries[i].i;
                int last = a[m][c];
                FORD(i,m,2) a[i][c] = a[i-1][c];
                a[1][c] = last;
            }
        }
        FOR(i,1,m) {
            FOR(j,1,n) printf("%lld ", a[i][j]);
            puts("");
        }
    }
}
