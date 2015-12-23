
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

const int MN = 100111;
int a[MN], b[MN], f[MN];
int n;
pair<int,int> x[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d%d", &x[i].first, &x[i].second);
        sort(x+1, x+n+1);
        FOR(i,1,n) {
            a[i] = x[i].first;
            b[i] = x[i].second;
        }
        int res = n;
        FOR(i,1,n) {
            if (i == 1) f[i] = 0;
            else {
                int j = lower_bound(a+1, a+i+1, a[i] - b[i]) - a - 1;
                f[i] = f[j] + i - j - 1;
            }
            res = min(res, f[i] + n-i);
        }
//        PR(f, n);
        cout << res << endl;
    }
}
