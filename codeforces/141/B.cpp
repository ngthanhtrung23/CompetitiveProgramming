
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
    int a, x, y;
    while (cin >> a >> x >> y) {
        if (y % a == 0) cout << -1 << endl;
        else {
            int id = 1, bottom = 0;
            for(; bottom + a < y; bottom += a) {
                if (bottom == 0) ++id;
                else if (bottom % (2*a)) ++id;
                else id += 2;
            }
//            DEBUG(id);

            int right = a / 2 + a % 2;
            int left = -right;
            int typ = 1;
            if (bottom && bottom % (2*a) == 0) {
                left = -a;
                right = a;
                typ = 2;
            }

            if (left < x && x < right) {
                if (typ == 1) cout << id << endl;
                else if (typ == 2) {
                    if (x == 0) cout << -1 << endl;
                    else if (x > 0) cout << id+1 << endl;
                    else cout << id << endl;
                }
            }
            else cout << -1 << endl;
        }
    }
}
