
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

bool forced;

int get(int x, int y) {
    if (x == 0 || y == 0) {
        forced = true;
        return 1;
    }
    if (x < 0 && y < 0) return get(-x, -y);
    else if (x < 0 || y < 0) return 1 - get(abs(x), abs(y));

    int sum = x*x + y*y;
    int i, color;
    for(i = 1, color = 1; i*i < sum; ++i, color = 1 - color);

    if (sum == i*i) {
        forced = true;
        return 1;
    }

    return color;
}

int main() {
    int x, y;
    while (cin >> x >> y) {
        forced = false;
        int res = get(x, y);
        if (forced) res = 1;
        cout << (res ? "black" : "white") << endl;
    }
    return 0;
}

