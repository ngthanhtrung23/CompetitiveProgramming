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

int extgcd(int a, int b, int &x, int &y) {
    int g = a; x = 1; y = 0;
    if (b != 0) g = extgcd(b, a % b, y, x), y -= (a / b) * x;
    return g;
}

long long powMod(long long x, int k, int n) {
    if (k == 0) return 1 % n;
    if (k == 1) return x % n;

    long long mid = powMod(x, k >> 1, n);
    mid = mid * mid % n;

    if (k & 1) return mid * x % n;
    else return mid;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n, e, c;
    while (cin >> n >> e >> c) {
        int p, q;
        for(int i = 2; i*i <= n; ++i)
            if (n % i == 0) {
                p = i;
                q = n / i;
                break;
            }

        int phi = (p - 1) * (q - 1);
        int x, y;
        extgcd(e, phi, x, y);

        int d = x % phi;
        if (d < 0) d += phi;

        cout << powMod(c, d, n) << endl;
    }
    return 0;
}
