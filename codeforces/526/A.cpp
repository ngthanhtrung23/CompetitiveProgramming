
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

int n;
string s;

bool good(int u) {
    return u < n && s[u] == '*';
}

int main() {
    while (cin >> n >> s) {
        bool ok = false;
        FOR(d,1,n-1) {
            REP(i1,n)
                if (good(i1) && good(i1+d) && good(i1+2*d)
                        && good(i1+3*d) && good(i1+4*d))
                    ok = true;
        }
        if (ok) cout << "yes"; else cout << "no";
        cout << endl;
    }
    return 0;
}
