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

string a, b;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> a >> b) {
        bool ok = true;
        int j = 0;
        REP(i,a.length()) {
            while (j < b.length() && b[j] != a[i]) ++j;
            if (j >= b.length()) {
                ok = false;
                break;
            }
            ++j;
        }
//        DEBUG(j);

        int k = b.length() - 1;
        FORD(i,a.length()-1,0) {
            while (k >= 0 && b[k] != a[i]) --k;
            if (k < 0) {
                ok = false;
                break;
            }
            --k;
        }
//        DEBUG(k);

        if (ok) cout << max(k - j + 2, 0) << endl;
        else cout << 0 << endl;
    }
    return 0;
}
