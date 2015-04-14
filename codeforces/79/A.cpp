
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
    int x, y;
    while (cin >> x >> y) {
        while (true) {
            int cx = -1, cy = -1;
            FORD(ix,2,0) {
                int iy = (220 - (ix * 100)) / 10;
                if (ix <= x && iy <= y) {
                    cx = ix;
                    cy = iy;

                    x -= ix;
                    y -= iy;
                    break;
                }
            }
            if (cx < 0) { cout << "Hanako" << endl; break; }

            cx = cy = -1;
            FOR(ix,0,2) {
                int iy = (220 - (ix * 100)) / 10;
                if (ix <= x && iy <= y) {
                    cx = ix;
                    cy = iy;

                    x -= ix;
                    y -= iy;
                    break;
                }
            }
            if (cx < 0) { cout << "Ciel" << endl; break; }
        }
    }
    return 0;
}
