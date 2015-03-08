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
    int n;
    while (cin >> n) {
        map<string,int> f;
        f["polycarp"] = 1;
        int res = 0;
        FOR(i,1,n) {
            string a, tmp, b;
            cin >> a >> tmp >> b;
            REP(i,a.length()) if (a[i] >= 'A' && a[i] <= 'Z') a[i] ^= ' ';
            REP(i,b.length()) if (b[i] >= 'A' && b[i] <= 'Z') b[i] ^= ' ';
            f[a] = f[b] + 1;
            res = max(res, f[a]);
        }
        cout << res << endl;
    }
    return 0;
}

