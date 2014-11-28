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

bool ok[3011];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n;
    while (cin >> n) {
        string s; cin >> s;
        memset(ok, true, sizeof ok);

        REP(i,s.length()) {
            if (s[i] == 'R') {
                int j = i + 1;
                while (j < s.length() && s[j] != 'L') ++j;
                if (s[j] == 'L') {
                    for(int x = i, y = j; x < y; ++x, --y)
                        ok[x] = ok[y] = false;
                    s[j] = '.';
                }
                else FOR(x,i,n-1) ok[x] = false;
            }
            else if (s[i] == 'L') {
                REP(x,i+1) ok[x] = false;
            }
        }
        int cnt = 0;
        REP(x,n) if (ok[x]) ++cnt;
        cout << cnt << endl;
    }
    return 0;
}
