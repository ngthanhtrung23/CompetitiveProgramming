
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
using namespace std;

int main() {
    ios :: sync_with_stdio(false);
    int n; string s;
    while (cin >> n >> s) {
        int res = 0;

        REP(i,n) if (s[i] == 'N') {
            int nf = 0, na = 0;
            REP(j,i) if (s[j] == 'F') ++nf;

            FOR(j,i+1,n-1) if (s[j] == 'A') ++na;

            res += min(na, nf);
        }

        REP(i,n) if (s[i] == 'F')
            FOR(j,i+1,n-1) if (s[j] == 'A')
                ++res;
        cout << res << endl;
    }
}
