
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
    string a, b;
    while (cin >> a >> b) {
        int cnt = 0;
        int u = -1, v = -1;
        int n = a.length();

        if (a.length() != b.length()) {
            puts("NO");
            continue;
        }

        REP(i,n) if (a[i] != b[i]) {
            if (cnt == 0) u = i;
            else if (cnt == 1) v = i;
            ++cnt;
        }

        if (cnt == 1 || cnt > 2 || a[u] != b[v] || a[v] != b[u]) puts("NO");
        else puts("YES");
    }
    return 0;
}
