
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

int main() {
    ios :: sync_with_stdio(false);
    string s;
    while (cin >> s) {
        string res = "";
        int n = s.length();
        for(int mask = 0; mask < (1<<n); ++mask) {
            string cur = "";
            for(int i = 0; i < n; ++i)
                if ((mask >> i) & 1)
                    cur += s[i];

            string rev = cur;
            reverse(rev.begin(), rev.end());

            if (rev == cur) res = max(res, cur);
        }
        cout << res << endl;
    }
    return 0;
}
