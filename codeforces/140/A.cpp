
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

int n;
double R, r;

bool can() {
    if (n == 1) return R >= r;
    else if (n == 2) return R >= 2*r;
    else {
        if (r > R) return false;

        double a = R - r;
        double b = r + r;
        double alpha = acos((a*a + a*a - b*b) / 2.0 / a / a);
        alpha *= n;

        return (alpha < 2*acos(-1.0) + 1e-9);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> R >> r) {
        cout << (can() ? "YES" : "NO") << endl;
    }
}
