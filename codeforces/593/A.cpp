
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

string a[111];
int n;

bool can(string s, char c1, char c2) {
    REP(i,SZ(s))
        if (s[i] != c1 && s[i] != c2)
            return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        int res = 0;
        FOR(c1,'a','z') FOR(c2,'a','z') {
            int cur = 0;
            FOR(i,1,n) if (can(a[i], c1, c2)) {
                cur += SZ(a[i]);
            }
            res = max(res, cur);
        }
        cout << res << endl;
    }
}
