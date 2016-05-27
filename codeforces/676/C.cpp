
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

int suma[1000111];

int get(int l, int r) {
    int len = r - l + 1;
    int a = suma[r] - suma[l-1];

    return min(a, len - a);
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n, k;
    string s;
    while (cin >> n >> k >> s) {
        s = " " + s + " ";
        FOR(i,1,n)
            if (s[i] == 'a') suma[i] = suma[i-1] + 1;
            else suma[i] = suma[i-1];

        int ans = 0;
        FOR(i,1,n) {
            int res = i;
            int l = 1, r = i;
            while (l <= r) {
                int mid = (l + r) >> 1;
                if (get(mid, i) <= k) {
                    res = mid;
                    r = mid  - 1;
                }
                else l = mid + 1;
            }

            ans = max(ans, i - res + 1);
        }
        cout << ans << endl;
    }
}
