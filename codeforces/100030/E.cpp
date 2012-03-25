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

int n, m;
ll fail[22];

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (scanf("%d%d", &n, &m) == 2) {
        memset(fail, 0, sizeof fail);
        REP(i,n) {
            int k, u; scanf("%d", &k);
            while (k--) {
                scanf("%d", &u);
                u--;
                fail[i] |= 1LL<<u;
            }
        }
        int res = n, save = (1<<n) - 1;
        REP(mask,1<<n) {
            ll all = 0;
            int now = 0;
            REP(i,n) if (mask & (1<<i)) {
                all |= fail[i];
                now++;
            }
            if (all == (1LL<<m) - 1 && now < res) {
                res = now;
                save = mask;
            }
        }
        printf("%d\n", res);
        REP(i,n) if (save & (1<<i)) printf("%d ", i+1);
        puts("");
    }
    return 0;
}
