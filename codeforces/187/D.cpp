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

const int MN = 200111;

void update(int &a, int b) {
    if (b < 0) return ;
    if (a < 0) a = b;
    else a = min(a, b);
}

int first[MN*6];
long long f[MN], a[MN], c[MN];
long long g, r;
int n;

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void insert(int i, int l, int r, int k, int val) {
    if (k < c[l] || c[r] < k) return ;
    update(first[i], val);
    if (l == r) {
        return ;
    }
    update(first[i], val);
    int mid = (l + r) >> 1;
    insert(CT(i), l, mid, k, val);
    insert(CP(i), mid+1, r, k, val);
}

int get(int i, int l, int r, int u, int v) {
    if (v < c[l] || c[r] < u) return -1;
    if (u <= c[l] && c[r] <= v) return first[i];
    int mid = (l + r) >> 1;
    int res = -1;
    update(res, get(CT(i), l, mid, u, v));
    update(res, get(CP(i), mid+1, r, u, v));
    return res;
}

int main() {
    memset(first, -1, sizeof first);

    cin >> n >> g >> r;
    ++n;
    FOR(i,1,n) {
        int x; scanf("%d", &x);
        a[i] = a[i-1] + x;
        c[i] = a[i] % (g+r);
    }

    sort(c+1, c+n+1);
    int sz = unique(c+1, c+n+1) - c - 1;

    f[n] = 0;

    FORD(i,n-1,0) {
        int x = -1;
        long long first, last;
        first = (g + a[i]) % (g + r);
        last = (g + r - 1 + a[i]) % (g + r);

        if (first <= last) {
            update(x, get(1, 1, sz, first, last));
        }
        else {
            update(x, get(1, 1, sz, first, g+r-1));
            update(x, get(1, 1, sz, 0, last));
        }

        if (x == -1) {
            f[i] = a[n] - a[i];
        }
        else {
            f[i] = a[x] - a[i];
            f[i] = f[i] - f[i] % (g+r) + (g+r);

            f[i] += f[x];
        }

        // cout << first << ' ' << last << endl;
        // cout << i << ' ' << a[i] << ' ' << x << ' ' << f[i] << endl;

        if (i) insert(1, 1, sz, a[i] % (g+r), i);
    }

    int q; scanf("%d", &q);
    while (q--) {
        int start; scanf("%d", &start);
        int x = -1;
        long long first, last;
        first = (g - start) % (g+r);
        last = (g+r-1 - start) % (g+r);

        if (first < 0) first += (g+r);
        if (last < 0) last += (g+r);

        long long res;

        if (first <= last) {
            update(x, get(1, 1, sz, first, last));
        }
        else {
            update(x, get(1, 1, sz, first, g+r-1));
            update(x, get(1, 1, sz, 0, last));
        }

        if (x == -1) {
            res = start + a[n];
        }
        else {
            res = start + a[x];
            res = res - res % (g+r) + g+r;
            res += f[x];
        }

        // cout << first << ' ' << last << endl;
        // cout << start << ' ' << x << ' ' << res << endl;

        printf("%I64d\n", res);
    }
    return 0;
}
