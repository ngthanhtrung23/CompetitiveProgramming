
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

int n, k;
string s[311];
int a[311], lcp[311][311];
ll f[311][311];

int getSame(string a, string b) {
    if (SZ(a) > SZ(b)) swap(a, b);
    int same = 0;
    while (same < SZ(a) && same < SZ(b) && a[same] == b[same]) ++same;
    return same;
}

void update(ll&x, ll val) {
    x = min(x, val);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n >> k;
        FOR(i,1,n) cin >> s[i];
        sort(s+1, s+n+1);

        FOR(i,1,n) {
            a[i] = SZ(s[i]);
        }
        FOR(i,1,n) FOR(j,i,n) lcp[i][j] = getSame(s[i], s[j]);

        // DP
        FOR(i,0,n) FOR(j,0,n) f[i][j] = 1e9;
        f[0][0] = 0;

        FOR(i,1,n) f[i][1] = a[i];

        FOR(i,1,n) FOR(x,1,k-1) if (f[i][x] < 1e9) {
            FOR(j,i+1,n)
                update(f[j][x+1], f[i][x] + a[i] - 2 * lcp[i][j] + a[j]);
        }

        ll res = 1e18;
        FOR(i,k,n) res = min(res, f[i][k] + a[i]);
        cout << "Case #" << test << ": " << res + k << endl;
    }
}
