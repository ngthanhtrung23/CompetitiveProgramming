
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

string s;
bool mark[2][311];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> s) {
        if (s.length() > 'z' - 'a' + 1) {
            cout << "IMPOSSIBLE" << endl;
        }
        else {
            memset(mark, false, sizeof mark);
            for(char c : s)
                mark[0][c] = true;

            REP(i,s.length()) {
                if (mark[1][s[i]]) {
                    s[i] = 'a';
                    while (mark[1][s[i]] || mark[0][s[i]]) ++s[i];
                }
                mark[1][s[i]] = true;
            }
            cout << s << endl;
        }
    }
    return 0;
}
