
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
#define double long double
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max((double) 0.0,x));
}
int GI(ll& x) {
    return scanf("%lld", &x);
}

const int MN = 200111;
int n, k;
double f[55][MN];
int s[MN], t[MN];
double st[MN], ot[MN], sum_st[MN], sum_ot[MN];
const double inf = 1e100;

double getCost(int l, int r) {
    return sum_st[r] - sum_st[l-1] - s[l-1] * (sum_ot[r] - sum_ot[l-1]);
}
void compute(int i, int L, int R, int optL, int optR) {
    if (L > R) return ;

    int mid = (L + R) >> 1, savek = optL;
    f[i][mid] = inf;
    FOR(k,optL,min(mid-1, optR)) {
        double cur = f[i-1][k] + getCost(k+1, mid);
        if (cur < f[i][mid]) {
            f[i][mid] = cur;
            savek = k;
        }
    }
    compute(i, L, mid-1, optL, savek);
    compute(i, mid+1, R, savek, optR);
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1 && GI(k) == 1) {
        FOR(i,1,n) {
            GI(t[i]);
            s[i] = s[i-1] + t[i];
        }
        FOR(i,1,n) {
            st[i] = s[i] / (double) t[i];
            ot[i] = 1.0 / (double) t[i];

            sum_st[i] = sum_st[i-1] + st[i];
            sum_ot[i] = sum_ot[i-1] + ot[i];
        }

        f[0][0] = 0.0;
        FOR(i,1,n) f[0][i] = inf;

        FOR(i,1,k) {
            compute(i, 1, n, 0, n);
        }
        cout << f[k][n] << endl;
    }
}
