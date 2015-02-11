
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

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    string s;
    while (cin >> s) {
        bool ok = false;
        REP(pos,s.length()+1) FOR(ad,'a','z') {
            if (ok) break;
            string add = ""; add += ((char) (ad));
            string t = s.substr(0, pos) + add + s.substr(pos);

            string tt = t; reverse(tt.begin(), tt.end());

            if (t == tt) {
                cout << t << endl;
                ok = true;
                break;
            }
        }
        if (!ok) cout << "NA" << endl;
    }
    return 0;
}
