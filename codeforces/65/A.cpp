
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

#define RON { cout << "Ron" << endl; continue; }
#define HER { cout << "Hermione" << endl; continue; }

int main() {
    ios :: sync_with_stdio(false);
    int a, b, c, d, e, f;
    // a sand --> b lead
    // c lead --> d gold
    // e gold --> f sand
    while (cin >> a >> b >> c >> d >> e >> f) {
        if (d == 0) HER;

        // convert directly 0 lead --> gold
        if (c == 0 && d > 0) RON;

        if (b == 0) HER;
        if (a == 0 && b > 0 && d > 0) RON;

        if (f == 0) HER;
        if (e == 0) RON;

        double has = 1;
        has = has / a * b;
        has = has / c * d;
        has = has / e * f;

        if (has > 1) RON;
        HER;
    }
    return 0;
}
