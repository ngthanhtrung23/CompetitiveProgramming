#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

int n, m, s;

long long pos(long long a, long long b) {
    return (m - a + 1) * (n - b + 1);
}

#define LEN(x) (((x)<<1) + 1)

bool check(int a, int b, int c, int d, int x0, int y0) {
    if (x0 - a < 1 || x0 + a > m) return false;
    if (x0 - c < 1 || x0 + c > m) return false;
    if (y0 - b < 1 || y0 + b > n) return false;
    if (y0 - d < 1 || y0 + d > n) return false;

    int cnt = 0;
    for(int i = 1; i <= m; i++)
        for(int j = 1; j <= n; j++)
            if ((abs(i - x0) <= a && abs(j - y0) <= b) ||
                (abs(i - x0) <= c && abs(j - y0) <= d))
                ++cnt;
    return cnt == s;
}

int brute() {
    int res = 0;
    for(int a = 0; LEN(a) <= m; a++)
        for(int b = 0; LEN(b) <= n; b++)
            for(int c = 0; LEN(c) <= m; c++)
                for(int d = 0; LEN(d) <= n; d++)
                    for(int x0 = 1; x0 <= m; x0++)
                        for(int y0 = 1; y0 <= n; y0++)
                            if (check(a,b,c,d,x0,y0)) ++res;
    return res;
}

int main() {
    while (scanf("%d%d%d", &n, &m, &s) == 3) {
        long long res = 0, now;
        // c > a, b > d
        for(int a = 0; LEN(a) <= m; a++)
            for(int b = 0; LEN(b) <= n; b++) {
                int s2 = s - LEN(a) * LEN(b);
                if (s2 < 0) continue;

                for(int c = a+1; LEN(c) <= m; c++) {
                    if (s2 % (2*c - 2*a) == 0) {
                        int d = s2 / (2*c - 2*a);
                        if (d % 2 == 0) continue;

                        d = (d - 1) / 2;

                        if (d >= b) continue;

                        res += pos(LEN(c), LEN(b));
                    }
                }
            }

        // c > a, d >= b
        for(int c = 1; LEN(c) <= m; c++)
            for(int d = 0; LEN(d) <= n; d++)
                if (LEN(c) * LEN(d) == s) {
                    now = c * (d+1LL); // choose a, b
                    now *= pos(LEN(c), LEN(d));
                    res += now;
                }
        res *= 2;

        // c == a
        for(int c = 0; LEN(c) <= m; c++)
            for(int x = 0; LEN(x) <= n; x++)
                if (LEN(c) * LEN(x) == s) {
                    now = 2 * x + 1; // choose b, d
                    now *= pos(LEN(c), LEN(x));
                    res += now;
                }

        cout << res << endl;
    }
    return 0;
}
