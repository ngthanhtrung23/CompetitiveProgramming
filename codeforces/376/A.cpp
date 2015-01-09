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

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> s) {
        int u = s.find('^');
        assert(s[u] == '^');

        long long left = 0, right = 0;
        REP(i,s.size())
            if (s[i] >= '0' && s[i] <= '9') {
                int cur = abs(u - i) * (s[i] - '0');
                if (i < u) left += cur;
                else right += cur;
            }
        if (left == right) cout << "balance";
        else if (left > right) cout << "left";
        else cout << "right";
        cout << endl;
    }
    return 0;
}
