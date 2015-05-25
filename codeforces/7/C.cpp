
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

long long extgcd(long long a, long long b, long long &x, long long &y) {
    int g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}

int main() {
    ios :: sync_with_stdio(false);
    long long a, b, c;
    while (cin >> a >> b >> c) {
        if (a == 0) {
            if (c % b) cout << -1 << endl;
            else cout << 0 << ' ' << -c/b << endl;
        }
        else if (b == 0) {
            if (c % a) cout << -1 << endl;
            else cout << -c/a << ' ' << 0 << endl;
        }
        else {
            long long g = __gcd(llabs(a), llabs(b));
            if (c % g) {
                cout << -1 << endl;
                continue;
            }
            // now some solution must exist
            a /= g;
            b /= g;
            c /= g;

            long long x, y;

            int signa, signb;
            if (a > 0) signa = 1;
            else signa = -1, a = -a;

            if (b > 0) signb = 1;
            else signb = -1, b = -b;

            extgcd(a, b, x, y);
            assert(llabs(x) <= 2000111000);
            assert(llabs(y) <= 2000111000);

            x *= signa;
            y *= signb;

            x *= -c;
            y *= -c;
            assert(signa*a*x+signb*b*y+c == 0);
            cout << x << ' ' << y << endl;
        }
    }
    return 0;
}

