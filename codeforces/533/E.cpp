
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
#define SZ(X) ((int) ((X).size()))
using namespace std;

int main() {
    ios :: sync_with_stdio(false);
    int n;
    string s, t;
    while (cin >> n >> s >> t) {
        int diff = 0;
        REP(i,n) if (s[i] != t[i]) ++diff;
        if (diff == 1) {
            cout << 2 << endl;
            continue;
        }
        int lcp = 0;
        while (s[lcp] == t[lcp]) ++lcp;
        int lcs = 0;
        while (s[n-1-lcs] == t[n-1-lcs]) ++lcs;
//        DEBUG(lcs);
//        DEBUG(lcp);

        s.erase(0, lcp);
        t.erase(0, lcp);
//        DEBUG(s);
//        DEBUG(t);

        s.erase(s.length() - lcs);
        t.erase(t.length() - lcs);
//        DEBUG(s);
//        DEBUG(t);

        int res = 0;
        if (s.substr(1) == t.substr(0, t.length()-1)) ++res;
        if (s.substr(0, s.length()-1) == t.substr(1)) ++res;
        cout << res << endl;
    }
}

