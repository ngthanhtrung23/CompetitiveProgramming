
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
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;

int n, k, a[MN];
string s;

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> k >> s) {
        s = " " + s + " ";
        int t = 0;
        FOR(i,1,n) if (s[i] == '0') a[++t] = i;

        n = t;
        ++k;

//        PR(a, n);

        int res = MN;
        FOR(l,1,n) {
            int r = l + k - 1;
            if (r > n) break;

            int mid = (a[l] + a[r]) / 2;
            int x = lower_bound(a+l, a+r+1, mid) - a;

            FOR(y,x-5,x+5) if (y >= l && y <= r) {
                int cur = max(llabs(a[y] - a[l]), llabs(a[y] - a[r]));
                res = min(res, cur);
            }
        }
        cout << res << endl;
    }
}
