#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
#define int long long

int debug = false;

int gcd(int a, int b, int &x, int &y) {
    if (a == 0) {
        x = 0; y = 1;
        return b;
    }
    int x1, y1;
    int d = gcd(b%a, a, x1, y1);
    x = y1 - (b / a) * x1;
    y = x1;
    return d;
}

bool find_any_solution(int a, int b, int c, int &x0, int &y0, int &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

int fib[1011];

bool check(int mid, int x0, int y0, int a, int b, int c, int &x, int &y) {
    int k = min((mid - y0) / (a), (x0 - 1) / (b));
    x = x0 - k * b;
    y = y0 + k * a;
    if (x < 0 && y > mid) {
        x += b;
        y -= a;
    }
    if (y > mid) {
        x += b;
        y -= a;
    }
    if (x < 0) {
        x += b;
        y -= a;
    }

    if (x >= 0 && y <= mid && x <= y) return true;
    return false;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    fib[1] = fib[2] = 1;
    FOR(i,3,66) fib[i] = fib[i-1] + fib[i-2];

    // PR(fib, 66);
    int ntest; cin >> ntest;
    while (ntest--) {
        int n; cin >> n;
        int best = n - n / 2;
        int savex = n/2, savey = n - n/2;
        FOR(i,1,65) if (fib[i+1] <= n) {
            int g, x0, y0;
            int a = fib[i], b = fib[i+1], c = n;
            g = __gcd(__gcd(a, b), c);
            a /= g;
            b /= g;
            c /= g;
            if (find_any_solution(a, b, c, x0, y0, g)) {
                int l = 1, r = best, res = r;
                while (l <= r) {
                    int mid = (l + r) / 2, x, y;
                    if (debug) {
                        DEBUG(mid);
                        DEBUG(check(mid, x0, y0, a, b, c, x, y));
                        DEBUG(x);
                        DEBUG(y);
                    }
                    if (check(mid, x0, y0, a, b, c, x, y)) {
                        r = mid - 1;

                        if (y < best) {
                            best = y;
                            savex = x; savey = y;
                        }
                    }
                    else l = mid + 1;
                }
            }
        }
        while (savey - savex <= savex && savey - savex > 0) {
            int next = savey - savex;
            savey = savex;
            savex = next;
        }
        cout << savex << ' ' << savey << endl;
    }
    return 0;
}
