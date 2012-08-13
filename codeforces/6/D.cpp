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

int f[11][22][22][22], tr[11][22][22][22], n, a, b, h[11], N;

int get(int n, int x, int y, int z, bool print = false) {
    if (x < 0) x = 0;
    if (y < 0) y = 0;
    if (z < 0) z = 0;
//    if (print) cout << endl << n << ' ' << x << ' ' << y << ' ' << z << endl;

    if (n == 0 && x == 0 && y == 0 && z == 0) return 0;
    if (!print && f[n][x][y][z] >= 0) return f[n][x][y][z];

    if (z == 0 && n > 0) {
        return get(n-1, h[n], x, y, print);
    }

    int res = 1000111000;
    if (!print) {
        res = min(res, get(n, x-b, y-a, z-b) + 1);
        if (n < N - 3)
            if (z || y) res = min(res, get(n, x, y-b, z-a) + 1);
    }
    else {
        if (f[n][x][y][z] == get(n, x-b, y-a, z-b) + 1) {
            printf("%d ", n+2);
            get(n, x-b, y-a, z-b, true);
        }
        else {
            printf("%d ", n+3);
            get(n, x, y-b, z-a, true);
        }
    }
    return f[n][x][y][z] = res;
}

int main() {
    while (scanf("%d%d%d", &n, &a, &b) == 3) {
        N = n;
        memset(h, 0, sizeof h);
        memset(f, -1, sizeof f);

        FOR(i,1,n) {
            scanf("%d", &h[i]);
            ++h[i];
        }
        printf("%d\n", get(n, 0, 0, 0));
        get(n, 0, 0, 0, true);
        puts("");
    }
    return 0;
}
