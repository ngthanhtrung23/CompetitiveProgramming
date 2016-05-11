
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

int n;
string a[1011];

int count(int l) {
    map<string,int> cnt;
    int res = 0;
    FOR(i,1,n) {
        if (SZ(a[i]) < l) continue;
        string cur = a[i].substr(SZ(a[i]) - l);
        cnt[cur] += 1;
        res = max(res, cnt[cur]);
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cout << "Case " << test << ":\n";
        cin >> n;
        FOR(i,1,n) {
            cin >> a[i];
            REP(j,SZ(a[i]))
                if (a[i][j] >= 'A' && a[i][j] <= 'Z')
                    a[i][j] ^= ' ';
        }
        int l = 0, r = 100, res = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (count(mid) >= 3) res = mid, l = mid + 1;
            else r = mid - 1;
        }
        cout << res << ' ' << count(res) << '\n';
    }
}
