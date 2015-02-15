
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
    cout << (fixed) << setprecision(9);
    int n, x0, y0;
    while (cin >> n >> x0 >> y0) {
        set< pair<int,int> > s;
        while (n--) {
            int x, y; cin >> x >> y;
            x -= x0; y -= y0;
            if (y < 0) {x = -x; y = -y;}

            if (x == 0) s.insert(make_pair(0, 1));
            else if (y == 0) s.insert(make_pair(1, 0));
            else s.insert(make_pair(x / __gcd(x, y), y / __gcd(x, y)));
        }
        cout << s.size() << endl;
    }
    return 0;
}
