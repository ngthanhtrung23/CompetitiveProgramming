#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

string a[111];
int n, q;

bool check(string &s) {
    FOR(i,1,n) if (a[i] == s) return true;

    int cnt = 0;
    FOR(i,1,n) {
        if (s.length() != a[i].length()) continue;
        int eq = s.length();

        REP(x,s.length())
            if (s[x] != a[i][x]) --eq;
        if (eq == s.length() - 1) ++cnt;
    }
    return cnt == 1;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cout << "Case #" << test << ":\n";
        cin >> n >> q;
        FOR(i,1,n) cin >> a[i];
        while (q--) {
            string s; cin >> s;
            if (check(s)) cout << "yes"; else cout << "no"; cout << endl;
        }
    }
    return 0;
}
