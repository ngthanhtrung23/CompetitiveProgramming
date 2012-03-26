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
const int MN = 100111;

int n, k, h, w[MN], v[MN], f[MN], tr[MN];
pair< pair<int,ll>, int> a[MN];

bool check(long double t) {
    FOR(i,1,n) {
        a[i].F.S = (ll) floor(v[a[i].S] * t + 1e-9) / h;
    }
    f[0] = 0;
    FOR(i,1,n) {
        f[i] = f[i-1];
        tr[i] = tr[i-1];
        if (a[i].F.S >= f[i] + 1) {
            f[i]++;
            tr[i] = i;
        }
    }
    return f[n] >= k;
}

int save[MN];

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d", &n) == 1) {
        scanf("%d%d", &k, &h);
        FOR(i,1,n) scanf("%d", &w[i]);
        FOR(i,1,n) scanf("%d", &v[i]);
        
        FOR(i,1,n) {
            a[i].F.F = w[i];
            a[i].F.S = v[i];
            a[i].S = i;
        }
        sort(a + 1, a + n + 1);
    
        long double l = 0.0, r = 1e9 + 100, res = r;
        REP(turn,100) {
            long double mid = (l + r) / 2.0;
            if (check(mid)) {
                res = mid;
                r = mid;
            }
            else l = mid;
        }
        check(res);
//        PR(f, n);
//        PR(tr, n);
        int cur = n;
        FORD(i,k,1) {
            save[i] = a[tr[cur]].S;
            cur = tr[cur] - 1;
        }
        FOR(i,1,k) printf("%d ", save[i]);
        puts("");
    }
    return 0;
}
