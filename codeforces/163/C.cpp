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
const int MN = 200111;

pair<long double,int> a[MN];
int x[MN], n, l, v1, v2;
long double res[MN];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d%d%d", &n, &l, &v1, &v2) == 4) {
        int k = 1;
        a[k] = MP(-1, 0);
        int cur = 0;
        FOR(i,1,n) {
            scanf("%d", &x[i]);
            a[++k] = MP(x[i], -1);
            long double need = x[i] - l / (v1/(long double)v2 + 1);
            if (need < 0) need += 2*l;
            a[++k] = MP(need, 1);
            if (x[i] < need) cur++;
        }
        sort(a+1, a+k+1);
        
        memset(res, 0, sizeof res);
        FOR(i,1,k) {
            long double range;
            if (i == k) range = 2*l - a[i].F + a[1].F;
            else range = a[i+1].F - a[i].F;
            cur += a[i].S;
            res[cur] += range / (2*l);
        }
        FOR(i,0,n) printf("%.12lf\n", (double) res[i]);
    }
    return 0;
}
