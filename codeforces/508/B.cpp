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
        int nEven = 0, lastEven = -1;
        REP(i,s.size()) if ((s[i] - '0') % 2 == 0) {
            ++nEven;
            lastEven = i;
        }
        if (nEven == 0) cout << -1 << endl;
        else {
            bool ok = false;
            REP(i,s.size()) if ((s[i] - '0') % 2 == 0 && s[i] < s.back()) {
                swap(s[i], s[s.size()-1]);
                ok = true;
                break;
            }
            if (!ok) swap(s[lastEven], s[s.size()-1]);

            cout << s << endl;
        }
    }
    return 0;
}
