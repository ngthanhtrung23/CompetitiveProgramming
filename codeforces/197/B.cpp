#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iomanip>
#include <bitset>
#include <complex>

#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define FORD(i,a,b) for(int i = a; i >= b; --i)
#define REP(i,a) for(int i = 0; i < a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(x,n) cout << #x << " = "; FOR(__,1,n) cout << x[__] << ' '; puts("");
#define PR0(x,n) cout << #x << " = "; REP(__,n) cout << x[__] << ' '; puts("");
using namespace std;

int m, n, a[111], b[111];

int gcd(int a, int b) {
    if (!b) return a;
    return gcd(b, a%b);
}

int main() {
    while (cin >> m >> n) {
        FOR(i,0,m) cin >> a[i];
        FOR(i,0,n) cin >> b[i];
        if (m > n) {
            if (a[0]*b[0] > 0) puts("Infinity");
            else puts("-Infinity");
        }
        else if (m < n) {
            puts("0/1");
        }
        else {
            if (b[0] < 0) {
                a[0] = -a[0];
                b[0] = -b[0];
            }
            int g = gcd(abs(a[0]), abs(b[0]));
            cout << a[0]/g << '/' << b[0] / g << endl;
        }
    }
    return 0;
}