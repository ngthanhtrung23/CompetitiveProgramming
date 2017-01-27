
#include <sstream>
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 200111;

int a[MN], b[MN], c[MN], tmp[MN], d[MN], n;

int getCost(int a[]) {
    int res = llabs(a[1] - a[2]);
    FOR(i,1,n-1) res = min(res, llabs(a[i] - a[i+1]));
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        FOR(i,1,n) GI(a[i]);
        sort(a+1, a+n+1);

        int k = 0;
        for(int i = 1; i <= n; i += 2) b[i] = a[++k];
        for(int i = 2; i <= n; i += 2) b[i] = a[++k];

        int fb = getCost(b);

        k = 0;
        for(int i = 2; i <= n; i += 2) c[i] = a[++k];
        for(int i = 1; i <= n; i += 2) c[i] = a[++k];

        int fc = getCost(c);

        int fd = -1;

        if (n % 2 == 1 && n > 1) {
            int len = n / 2;
            k = 0;
            FORD(start,len,1) {
                int u = start;
                while (u <= n) {
                    tmp[++k] = a[u];
                    u += len;
                }
            }

            tmp[n+1] = tmp[1];

            int nn = abs(tmp[1] - tmp[2]);
            FOR(i,1,n) {
                int j = i+1;
                nn = min(nn, abs(tmp[i] - tmp[i+1]));
            }

            FOR(i,1,n) if (abs(tmp[i] - tmp[i+1]) == nn) {
                int u = i+1;
                FOR(turn,1,n) {
                    if (u > n) u -= n;
                    d[turn] = tmp[u];
                    ++u;
                }
                break;
            }

            fd = getCost(d);
        }


        FOR(i,1,n) {
            if (fb > fc && fb > fd) printf("%lld ", b[i]);
            else if (fc > fd) printf("%lld ", c[i]);
            else printf("%lld ", d[i]);
        }
        puts("");
    }
}
