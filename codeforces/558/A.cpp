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

int n1, n0;
pair<int,int> a[2][111];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        n1 = n0 = 0;
        FOR(i,1,n) {
            int x, y;
            cin >> x >> y;
            if (x < 0) a[1][++n1] = make_pair(-x, y);
            else a[0][++n0] = make_pair(x, y);
        }
        sort(a[0]+1, a[0]+n0+1);
        sort(a[1]+1, a[1]+n1+1);

        if (n1 > n0 + 1) n1 = n0 + 1;
        if (n0 > n1 + 1) n0 = n1 + 1;

        int res = 0;
        FOR(i,1,n0) res += a[0][i].second;
        FOR(i,1,n1) res += a[1][i].second;
        cout << res << endl;
    }
}
