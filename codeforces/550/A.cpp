
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

int f[2][2][100111];

int main() {
    ios :: sync_with_stdio(false);
    string s;
    while (cin >> s) {
        int n = s.length();
        s = " " + s;

        // f[0][0] = from left, AB
        // f[0][1] = from left, BA
        memset(f, 0, sizeof f);
        FOR(i,1,n) {
            if (s[i] == 'B' && s[i-1] == 'A') f[0][0][i] = true;
            else f[0][0][i] = f[0][0][i-1];

            if (s[i] == 'A' && s[i-1] == 'B') f[0][1][i] = true;
            else f[0][1][i] = f[0][1][i-1];
        }
        // f[1][0] = from right, AB
        // f[1][1] = from right, BA
        FORD(i,n,1) {
            if (s[i] == 'A' && s[i+1] == 'B') f[1][0][i] = true;
            else f[1][0][i] = f[1][0][i+1];

            if (s[i] == 'B' && s[i+1] == 'A') f[1][1][i] = true;
            else f[1][1][i] = f[1][1][i+1];
        }
        bool res = false;
        FOR(i,1,n-1)
            if ((f[0][0][i] && f[1][1][i+1])
                    || (f[0][1][i] && f[1][0][i+1]))
                res = true;
        cout << (res ? "YES" : "NO") << endl;
    }
    return 0;
}

