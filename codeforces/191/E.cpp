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
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; puts("");
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

vector<ll> it[400111];
int n;
ll k;
int a[100111];
ll sum[100111];

#define CT(x) ((x)<<1)
#define CP(x) (CT(x) + 1)

void build(int i, int l, int r) {
    it[i].clear();
    FOR(x,l,r) it[i].PB(sum[x]);
    if (l == r) {
//        PR0(it[i], it[i].size());
        return ;
    }
    
    sort(it[i].begin(), it[i].end());
//    PR0(it[i], it[i].size());
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);
}

int get(int i, int l, int r, int u, int v, ll x) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) {
        int cnt;
        if (x < it[i][0]) cnt = 0;
        else if (x >= it[i][it[i].size()-1]) cnt = it[i].size();
        else {
            cnt = upper_bound(it[i].begin(), it[i].end(), x) - it[i].begin();
        }
        return cnt;
    }
    int mid = (l + r) >> 1;
    return get(CT(i), l, mid, u, v, x) + get(CP(i), mid+1, r, u, v, x);
}

bool check(ll x) {
    ll can = 0;
//    DEBUG(x);
    FOR(i,2,n) {
        can += get(1,1,n,1,i-1,sum[i]-x);
//        DEBUG(can);
    }
    return can >= k;
}

const ll oo = 1000111000111000111LL;

void solve() {
    build(1,1,n);
    ll res = -oo, l = res, r = -res;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (check(mid)) {
            res = mid;
            l = mid+1;
        }
        else r = mid - 1;
    }
    cout << res << endl;
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d", &n) == 1) {
        cin >> k;
        n++;
        sum[1] = 0;
        FOR(i,2,n) {
            scanf("%d", &a[i]);
            sum[i] = sum[i-1] + a[i];
        }
        solve();
    }
    return 0;
}
