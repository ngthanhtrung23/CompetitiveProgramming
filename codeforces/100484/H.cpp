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

const int MN = 20111;
const int INC = 10001;

int k, n;
int bit[MN];
bool mark[MN];

#define _(x) ((x) & (-(x)))

int get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

void update(int u) {
    mark[u] = true;
    while (u < MN) {
        ++bit[u];
        u += _(u);
    }
}

struct Seg {
    int l, r;

    Seg(int l = 0, int r = 0) : l(l), r(r) {}
} all[MN];

bool operator < (const Seg &a, const Seg &b) {
    if (a.r != b.r) return a.r < b.r;
    return a.l > b.l;
}

int main() {
    ios :: sync_with_stdio(false);
    cin >> k >> n;
    FOR(i,1,n) {
        int a, b; cin >> a >> b;
        a += INC;
        b += INC;
        if (a > b) swap(a, b);

        all[i] = Seg(a, b);
    }
    sort(all+1, all+n+1);

    FOR(i,1,n) {
        int a = all[i].l, b = all[i].r;

        int can = min(b - a + 1, k);
        int has = get(b) - get(a - 1);

        if (has >= can) continue;

        FORD(t,b,a) {
            if (has == can) break;
            if (!mark[t]) {
                update(t);
                ++has;
            }
        }
    }

    int cnt = 0;
    REP(i,MN)
    if (mark[i]) ++cnt;
    cout << cnt << endl;
    REP(i,MN)
    if (mark[i]) cout << i - INC << endl;
    return 0;
}
