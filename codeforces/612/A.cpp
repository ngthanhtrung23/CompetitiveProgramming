
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
int n, p, q;
string s;

void solve() {
    int res = 1e9;
    int savea = -1, saveb = -1;
    FOR(a,0,100) {
        if (a * p <= n && (n - a*p) % q == 0) {
            int b = (n - a*p) / q;
            if (a + b < res) {
                res = a + b;
                savea = a;
                saveb = b;
            }
        }
    }
    if (res == 1e9) {
        cout << -1 << endl;
    }
    else {
        cout << res << endl;
        int cur = 0;
        FOR(i,1,savea) {
            REP(t,p) cout << s[cur++];
            cout << endl;
        }
        FOR(i,1,saveb) {
            REP(t,q) cout << s[cur++];
            cout << endl;
        }
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n >> p >> q) {
        cin >> s;
        solve();
    }
}
