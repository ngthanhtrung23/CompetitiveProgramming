
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

string s, t;
int n;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> s >> t) {
        int n = s.length();
        string res = "";

        int ds = 0, dt = 0;
        REP(i,n) {
            if (s[i] == t[i]) res += '0';
            else if (ds < dt) {
                res += '1' + '0' - s[i];
                ++ds;
            }
            else {
                res += s[i];
                ++dt;
            }
        }

        if (ds == dt) cout << res << endl;
        else cout << "impossible" << endl;
    }
    return 0;
}
