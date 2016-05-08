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

const int MN = 10111;
int n, r, last;
int a[2][MN];
int it[2][MN * 4];

void build(int row, int i, int l, int r) {
    if (l == r) {
        it[row][i] = a[row][l];
        return ;
    }
    int mid = (l + r) >> 1;
    build(row, i<<1, l, mid);
    build(row, i<<1|1, mid+1, r);

    it[row][i] = min(it[row][i<<1], it[row][i<<1|1]);
}

int get(int row, int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 1000111000111000111LL;
    if (u <= l && r <= v) return it[row][i];

    int mid = (l + r) >> 1;
    return min(
            get(row, i<<1, l, mid, u, v),
            get(row, i<<1|1, mid+1, r, u, v)
            );
}

int getMin(int row, int l, int r) {
    return get(row, 1, 1, n, l, r);
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest = 0;
    while (cin >> n >> r >> last && n) {
        FOR(i,1,n) cin >> a[0][i];
        FOR(i,1,n) cin >> a[1][i];

        build(0, 1, 1, n);
        build(1, 1, 1, n);

        cout << "Case " << ++ntest << ":\n";
        int ok = 0;
        FOR(j,1,n) {
            // if we start in (1, j)
            int full = a[1][j];

            if (r == 1) {
                if (getMin(1, j+1, n) >= full + 1
                        && getMin(0, last, n) >= full + 1
                        && getMin(0, 1, last-1) >= full
                        && getMin(1, 1, j) >= full) {


                    FOR(x,j+1,n) a[1][x] -= full+1;
                    FOR(x,last,n) a[0][x] -= full+1;
                    FOR(x,1,last-1) a[0][x] -= full;
                    FOR(x,1,j) a[1][x] -= full;

                    a[1][j] = full * 2 * n + (n - j) + (n - last + 1);

                    ok = 1;
                    break;
                }
            }
            else if (last >= j) {
                if (getMin(1, j+1, last) >= full + 1
                        && getMin(1, last+1, n) >= full
                        && getMin(0, 1, n) >= full
                        && getMin(1, 1, j) >= full) {

                    FOR(x,j+1,last) a[1][x] -= full+1;
                    FOR(x,last+1,n) a[1][x] -= full;
                    FOR(x,1,n) a[0][x] -= full;
                    FOR(x,1,j) a[1][x] -= full;

                    a[1][j] = full * 2 * n + (last - j);

                    ok = 1;
                    break;
                }
            }
            else if (last < j) {
                if (getMin(0, 1, n) >= full+1
                        && getMin(1, 1, last) >= full+1
                        && getMin(1, last+1, j) >= full
                        && getMin(1, j+1, n) >= full+1) {

                    FOR(x,1,n) a[0][x] -= full+1;
                    FOR(x,1,last) a[1][x] -= full+1;
                    FOR(x,last+1,j) a[1][x] -= full;
                    FOR(x,j+1,n) a[1][x] -= full+1;

                    a[1][j] += full * 2 * n + (n - j) + (last) + n;

                    ok = 1;
                    break;
                }
            }
        }
        if (!ok) cout << "INVALID\n";
        else {
            FOR(i,1,n) cout << a[0][i] << ' '; cout << endl;
            FOR(i,1,n) cout << a[1][i] << ' '; cout << endl;
        }
    }
}
