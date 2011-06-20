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
#include <sstream>
#include <iomanip>

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

int n, a[100111], f[100111], c[100111], res[100111];

#define _(u) (u & (-u))

void update(int u, int k) {
    f[u] = max(f[u], k);
    int v = u + _(u);
    if (v <= 100000) update(v, k);
}

int get(int u) {
    if (u < 1) return -1;
    int v = u - _(u);
    return max(get(v), f[u]);
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    scanf("%d", &n); FOR(i,1,n) scanf("%d", &a[i]);
    FOR(i,1,n) c[i] = a[i]; sort(c+1, c+n+1);
    int x = unique(c+1, c+n+1) - c - 1;
    FOR(i,1,n) a[i] = lower_bound(c+1, c+x+1, a[i]) - c;
    
    memset(f, -1, sizeof f);
    
    FORD(i,n,1) {
        int x = get(a[i] - 1);
        if (x == -1) res[i] = x;
        else res[i] = x - i - 1;
        update(a[i], i);
    }
    
    FOR(i,1,n) printf("%d ", res[i]);
    return 0;
}
