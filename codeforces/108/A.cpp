
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

void next(int& h, int& m) {
    ++m;
    if (m == 60) {
        h = (h + 1) % 24;
        m = 0;
    }
}

bool good(int h, int m) {
    return h / 10 == m % 10 && h % 10 == m / 10;
}

int main() {
    ios :: sync_with_stdio(false);
    int h, m;
    while (scanf("%d:%d", &h, &m) == 2) {
        next(h, m);
        while (!good(h, m)) next(h, m);

        printf("%02d:%02d\n", h, m);
    }
    return 0;
}
