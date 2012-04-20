//#pragma comment(linker, "/STACK:66777216")
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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i<_a; ++i)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int n, m, k, a[111][111], b[111][111], c[111][111], save[111][111];
char s[100111];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d%d\n", &n, &m, &k) == 3) {
        FOR(i,1,n) {
            gets(s);
            FOR(j,1,m) {
                scanf("%d%d%d\n", &a[i][j], &b[i][j], &c[i][j]);
                save[i][j] = c[i][j];
            }
        }
        int res = 0;
        FOR(i1,1,n) FOR(i2,1,n) {
            FOR(j,1,m) c[i1][j] = save[i1][j];
            
            int now = 0;
            FOR(kk,1,k) {
                int cur = 0, x, savej;
                FOR(j,1,m) if (c[i1][j]) {
                    x = b[i2][j] - a[i1][j];
                    if (x > cur) {
                        cur = x;
                        savej = j;
                    }
                }
                if (cur > 0) {
                    now += cur;
                    c[i1][savej]--;
                }
            }
            res = max(res, now);
        }
        cout << res << endl;
    }
    return 0;
}
