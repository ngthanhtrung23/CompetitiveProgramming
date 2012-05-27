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
#include <bitset>

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
#define PR0(a,n) cout << #a << " = "; REP(i,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

pair<int,int> a[100111];
ll sum[100111];
int ind[100111], n, k;

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d", &n, &k) == 2) {
        ll b; cin >> b;
        FOR(i,1,n) {
            scanf("%d", &a[i].F);
            a[i].S = i;
            a[i].F = - a[i].F;
        }
        sort(a+1, a+n);
        FOR(i,1,n-1) {
            a[i].F = -a[i].F;
            ind[a[i].S] = i;
        }
        FOR(i,1,n-1) sum[i] = sum[i-1] + a[i].F;
//        PR(sum, n-1); PR(ind, n-1);
        
        int res = n;
        FOR(i,1,n-1) {
            ll can = 0;
            can = sum[k];
            if (ind[i] > k) {
                can -= a[k].F;
                can += a[ind[i]].F;
            }
            if (can > b) {
                res = i;
                break;
            }
        }
        printf("%d\n", res);
    }
    return 0;
}
