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
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 1000111;

int n, a[MN], f[MN], g[MN], bit[MN];
#define _(x) ((x) & (-(x)))

void update(int u, int val) {
    while (u < MN) {
        bit[u] += val;
        u += _(u);
    }
}

int get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];

        map<int,int> cnt;
        FOR(i,1,n) {
            cnt[a[i]] += 1;
            f[i] = cnt[a[i]];
        }
        cnt.clear();
        FORD(i,n,1) {
            cnt[a[i]] += 1;
            g[i] = cnt[a[i]];
        }
        // PR(f,n);
        // PR(g,n);

        long long res = 0;
        FOR(i,1,n) update(g[i], 1);
        FOR(i,1,n) {
            update(g[i], -1);
            res += get(f[i] - 1);
        }
        cout << res << endl;
    }
    return 0;
}

