
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
long long f[1000111];

int main() {
    while (cin >> s) {
        if (s == "0") break;
        memset(f, 0, sizeof f);
        f[0] = 1;
        int l = s.length();
        FOR(i,0,l-1) {
            if (s[i] != '0') f[i+1] += f[i];
            if (s[i] != '0' && i < l-1 && (s[i] - '0') * 10 + s[i+1] - '0' <= 26) f[i+2] += f[i];
        }
        cout << f[l] << endl;
    }
    return 0;
}
