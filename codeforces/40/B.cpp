
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

int get(int m, int n, int x) {
    if (x > m || x > n) return 0;
    --x;
    int up = 1, down = m, left = 1, right = n;
    while (x) {
        ++up; --down;
        ++left; --right;
        --x;
    }
    if (up > down || left > right) return 0;

    int t = (down - up + 1) * (right - left + 1);
    return t / 2 + t % 2;
}

int main() {
    int m, n, x;
    while (cin >> m >> n >> x) {
        cout << get(m, n, x) - get(m, n, x+1) << endl;
    }
    return 0;
}

