#include <sstream>
#include <iomanip>
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

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);
const int MN = 500111;

struct Lady {
    int x, y, z;
} a[MN];

bool operator < (const Lady &a, const Lady &b) {
    return a.x < b.x;
}

int c[MN], bit[MN], k, n;

#define _(x) ((x) & -(x))

int get(int u) {
    int res = 0;
    while (u > 0) {
        res = max(res, bit[u]);
        u -= _(u);
    }
    return res;
}

void update(int u, int x) {
    while (u <= k) {
        bit[u] = max(bit[u], x);
        u += _(u);
    }
}

const int oo = 1000111000;

int main() {
    while (scanf("%d", &n) == 1) {
        memset(bit, 0, sizeof bit);

        FOR(i,1,n) scanf("%d", &a[i].x);
        FOR(i,1,n) scanf("%d", &a[i].y);
        FOR(i,1,n) scanf("%d", &a[i].z);

        FOR(i,1,n) {
            a[i].x = oo - a[i].x;
            a[i].y = oo - a[i].y;
        }

        sort(a+1, a+n+1);

        FOR(i,1,n) c[i] = a[i].y;
        sort(c+1, c+n+1);
        k = unique(c+1, c+n+1) - c - 1;
        FOR(i,1,n) a[i].y = lower_bound(c+1, c+k+1, a[i].y) - c;

        int j = 0, res = 0;
        FOR(i,1,n) {
            while (j < n && a[j+1].x < a[i].x) {
                ++j;
                update(a[j].y, a[j].z);
            }
            int z = get(a[i].y-1);
            if (z > a[i].z) ++res;
        }
        printf("%d\n", res);
    }
    return 0;
}
