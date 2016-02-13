
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
using namespace std;

const int MN = 2011;
int a[MN];
int cnt[10111], cnt2[10111];
const int ZERO = 5000;

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        sort(a+1, a+n+1);
        memset(cnt, 0, sizeof cnt);

        FOR(i,1,n) FOR(j,1,i-1) cnt[ZERO + a[i] - a[j]]++;
        FOR(i,1,n) FOR(j,1,i-1) cnt[ZERO + a[j] - a[i]]++;

        REP(i,10111) {
            cnt2[i] = cnt[i];
            if (i) cnt2[i] += cnt2[i-1];
        }

        double res = 0.0;
        FOR(a,ZERO+1,ZERO+5000)
            FOR(b,ZERO+1,ZERO+5000) {
                int maxc = - (a - ZERO) - (b - ZERO) - 1;
                maxc += ZERO;
                if (maxc < 0) continue;

                res += cnt[a] * (double) cnt[b] * (double) cnt2[maxc];
            }

        REP(turn,3) res /= n * (n - 1) / (double) 2.0;
        cout << (fixed) << setprecision(9) << res << endl;
    }
}
