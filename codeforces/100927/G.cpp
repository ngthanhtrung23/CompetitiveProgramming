
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

const int MN = 100111;
#define next next____
int a[MN], s[MN], t[MN], next[MN];

int sum, cnt;

bool check(int lt, int ls) {
    next[1] = 0;
    int j = 0;
    FOR(i,2,lt) {
        while (j > 0 && t[i] != t[j+1]) j = next[j];
        if (t[i] == t[j+1]) ++j;
        next[i] = j;
    }

    sum = 0; cnt = 0;
    j = 0;
    FOR(i,1,ls) {
        while (j > 0 && s[i] != t[j+1]) j = next[j];
        if (s[i] == t[j+1]) ++j;
        
        if (j == lt) {
            sum += s[i+1];
            cnt++;
            j = next[j];
        }
    }
    return cnt > 0;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("stocks.in", "r", stdin);
    freopen("stocks.out", "w", stdout);

    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n-1) s[i] = a[i+1] - a[i];

        int l = 1, r = n-2, res = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;

            int k = 0;
            FOR(i,n-mid,n-1) t[++k] = s[i];

            if (check(k, n-2)) {
                res = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }

        if (res == 0) cout << "impossible" << endl;
        else {
            int k = 0;
            FOR(i,n-res,n-1) t[++k] = s[i];

            check(res, n-2);

            sum += cnt * a[n];
            int g = __gcd(llabs(sum), llabs(cnt));
            cout << sum/g << '/' << cnt/g << endl;
        }
    }
}
