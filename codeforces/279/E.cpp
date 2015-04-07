
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

int f[2][1000111];
string s;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> s) {
        int n = s.length();
        // f[0][i] = minimum cost to create 0..i
        // f[1][i] = minimum cost to create negative 0..i
        REP(i,n) {
            if (i == 0) {
                if (s[i] == '0') {
                    f[0][i] = 0;
                    f[1][i] = 0;
                }
                else {
                    f[0][i] = 1;
                    f[1][i] = 1;
                }
            }
            else {
                if (s[i] == '0') {
                    f[0][i] = min(f[0][i-1], f[1][i-1] + 1);
                    f[1][i] = min(f[0][i-1] + 2, f[1][i-1] + 1);
                }
                else {
                    f[0][i] = min(f[0][i-1] + 1, f[1][i-1] + 2);
                    f[1][i] = min(f[0][i-1] + 1, f[1][i-1]);
                }
            }
        }
        cout << min(f[0][n-1], f[1][n-1] + 1) << endl;
    }
    return 0;
}
