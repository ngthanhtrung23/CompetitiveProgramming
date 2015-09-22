#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

#define left left_

int sz, a[1011], left[1011];
int n, k;
map<int,bool> memo[1011][33];

bool get(int i, int k, int sum) {
    // FOR(x,i,sz) cout << a[i] << ' '; cout << "   " << k << ' ' << sum << endl;
    if (memo[i][k].count(sum)) return memo[i][k][sum];
    if (sz - i + 1 < k) return memo[i][k][sum] = false;
    if (k == 0 && sum == 0) return memo[i][k][sum] = true;
    if (k == 0 && sum) return memo[i][k][sum] = false;
    if (left[i+k-1] - left[i-1] < sum) return memo[i][k][sum] = false;
    if (left[sz] - left[sz-k] > sum) return memo[i][k][sum] = false;

    FOR(cur,i,sz)
    if (get(cur+1, k-1, sum - a[cur]))
        return memo[i][k][sum] = true;
    return memo[i][k][sum] = false;
}

void trace(int i, int k, int sum) {
    if (k == 0) return ;
    FOR(cur,i,sz)
    if (get(cur+1, k-1, sum - a[cur])) {
        trace(cur+1, k-1, sum-a[cur]);
        cout << a[cur] << ' ';
        break;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("squary.in", "r", stdin);
    freopen("squary.out", "w", stdout);
    while (cin >> n >> k) {
        sz = 0;
        for(int i = 1; i*i < n; ++i)
            a[++sz] = n-i*i;
        left[0] = 0;
        FOR(i,1,sz) left[i] = left[i-1] + a[i];
        // PR(a,sz);
        // PR(sum, sz);

        FOR(i,1,sz) FOR(t,0,30) memo[i][t].clear();
        cout << (get(1, k, n) ? "YES" : "NO") << endl;
        trace(1, k, n);
        cout << endl;
    }
    return 0;
}