
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

int m, n;
char a[511][511];

int main() {
    while (cin >> n && n) {
        int t = 0;
        string s; cin >> s;
        int i = 0;
        while (t < s.length()) {
            ++i;
            FOR(j,1,n) {
                char c = (t < s.length()) ? s[t] : ' ';
                ++t;
                if (i % 2 == 1) a[i][j] = c;
                else a[i][n - j + 1] = c;
            }
        }
        int m = i;
        FOR(j,1,n) FOR(i,1,m) cout << a[i][j]; cout << "\n";
    }
    return 0;
}
