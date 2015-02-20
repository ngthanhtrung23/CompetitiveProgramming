
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
    long long r, h;
    while (cin >> r >> h) {
        double margin = sqrt(r*r - r*r / 4.0) - r / 2.0;
        int can = (h / r) * 2;
        double last = (h / r) * r - r / 2.0;
        if (last + r + margin <= h) can += 3;
        else if (last + r <= h) can += 2;
        else ++can;

        cout << can << endl;
    }
    return 0;
}
