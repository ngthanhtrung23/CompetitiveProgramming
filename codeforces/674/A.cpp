
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

const int MN = 5011;
int a[MN], cnt[MN], res[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);

        memset(res, 0, sizeof res);
        FOR(i,1,n) {
            memset(cnt, 0, sizeof cnt);
            int ln = 0, save = -1;
            FOR(j,i,n) {
                ++cnt[a[j]];
                if ((cnt[a[j]] > ln) || (cnt[a[j]] == ln && a[j] < save)) {
                    ln = cnt[a[j]];
                    save = a[j];
                }
                res[save]++;
            }
        }
        FOR(i,1,n) printf("%d ", res[i]);
        puts("");
    }
}
