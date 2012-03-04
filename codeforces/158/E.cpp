#include <iomanip>
#include <sstream>
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
using namespace std;

const double PI = acos(-1.0);
const int oo = 1000111;

int n, k, f[4011][4011], t[4011], d[4011];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d", &n, &k) == 2) {
        FOR(i,1,n) scanf("%d%d\n", &t[i], &d[i]);
        if (k == n) {
            printf("%d\n", 86400);
            continue;
        }
        FOR(i,0,n) FOR(j,0,k) f[i][j] = oo;
        f[0][0] = 0;
        FOR(i,0,n-1) FOR(j,0,k) if (f[i][j] < oo) {
            if (j < k) f[i+1][j+1] = min(f[i+1][j+1], f[i][j]);
            f[i+1][j] = min(f[i+1][j], max(f[i][j]+1, t[i+1]) + d[i+1] - 1);
        }
        int res = 0, last;
        FOR(i,0,n) FOR(j,0,k) if (f[i][j] < 86400) {
            if (i+k-j+1 <= n) last = t[i+k-j+1] - 1; else last = 86400;
            res = max(res, last - f[i][j]);
        }
        printf("%d\n", res);
    }
    return 0;
}
