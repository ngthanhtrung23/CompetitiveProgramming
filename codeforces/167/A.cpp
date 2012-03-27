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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int n, a, d;

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d%d", &n, &a, &d) == 3) {
        long double last = 0.0;
        FOR(i,1,n) {
            long double D = d;
            int t, v;
            scanf("%d%d", &t, &v);
            long double tx = v / (long double) a;
            long double best = a * tx*tx / 2.0, res;
            if (best > D) {
                res = t + sqrt(2*(long double) D / a);
            }
            else {
                res = t + tx;
                D -= best;
                res += D / (long double) v;
            }
            
            res = max(res, last);
            printf("%.8lf\n", (double) res);
            last = res;
        }
    }
    return 0;
}
