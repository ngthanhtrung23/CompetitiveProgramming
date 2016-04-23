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

int n;
pair<int,int> c[200111];
pair<ll,ll> sum[100111];

void update(ll x, ll sl, ll &res, ll &save) {
    ll cur = 0;
    cur = x * sl;
    if (x < sum[n].F) {
        int u = lower_bound(sum + 1, sum + n + 1, MP(x+1, 0LL)) - sum;
        cur += sum[u].S;
    }
    if (cur > res) {
        res = cur;
        save = x;
    }
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (scanf("%d", &n) == 1) {
        int a, b, k = 0;
        FOR(i,1,n) {
            scanf("%d%d", &a, &b);
            c[++k] = MP(a, -1);
            c[++k] = MP(b, 1);
            sum[i].F = a;
        }
        sort(sum+1, sum+n+1);
        sum[n+1] = MP(0,0);
        FORD(i,n,1) {
            sum[i].S = sum[i+1].S + sum[i].F;
        }
        sort(c+1, c+k+1);
        
        ll res = 0, save = 0, now = 0;
        FOR(i,1,k) {
            if (c[i].S == -1) {
                now++;
                update(c[i].F, now, res, save);
            }
            else {
                update(c[i].F, now, res, save);
                now--;
            }
        }
        cout << save << ' ' << res << endl;
    }
    return 0;
}