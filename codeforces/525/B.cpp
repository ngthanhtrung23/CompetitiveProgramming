
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
int a[200111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> s) {
        memset(a, 0, sizeof a);
        int l = s.length();
        s = " " + s;
        int q; cin >> q;
        while (q--) {
            int u; cin >> u;
            a[u]++;
            a[l - u + 2]--;
        }
        int cur = 0;
        FOR(i,1,l) {
            cur += a[i];
            if (cur % 2 == 0) cout << s[i];
            else cout << s[l - i + 1];
        }
        cout << endl;
    }
    return 0;
}

