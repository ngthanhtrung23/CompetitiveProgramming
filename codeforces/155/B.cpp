
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

pair<int,int> a[1011];

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        FOR(i,1,n) {
            int x, y; cin >> x >> y;
            a[i] = make_pair(-y, -x);
        }
        sort(a+1, a+n+1);
        int res = 0, cnt = 1;
        FOR(i,1,n) {
            res -= a[i].second;
            cnt -= a[i].first;
            --cnt;
            if (cnt == 0) break;
        }
        cout << res << endl;
    }
    return 0;
}
