#include <bits/stdc++.h>
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
int GI(ll& x) {
    return scanf("%lld", &x);
}

int n, k, a, b, c, d;

const int MN = 1011;
int x[MN], y[MN], mark[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int k;
    while (cin >> n >> k >> a >> b >> c >> d) {
        int need = n + 1;

        if (k < need || n == 4) {
            cout << -1 << endl;
            continue;
        }

        x[1] = a; x[2] = c; x[n-1] = d; x[n] = b;
        y[1] = c; y[2] = a; y[n-1] = b; y[n] = d;

        memset(mark, 0, sizeof mark);
        mark[a] = mark[b] = mark[c] = mark[d] = 1;

        int cur = 0;
        FOR(i,3,n-2) {
            ++cur;
            while (mark[cur]) ++cur;

            mark[cur] = 1;
            x[i] = y[i] = cur;
        }
        FOR(i,1,n) printf("%d ", x[i]); puts("");
        FOR(i,1,n) printf("%d ", y[i]); puts("");
    }
}
