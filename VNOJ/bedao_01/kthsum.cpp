#include "bits/stdc++.h"
#pragma GCC optimize("Ofast")
// Make __builtin_popcount faster: https://codeforces.com/blog/entry/13134?#comment-736517
#pragma GCC target("popcnt")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
 
#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }
 
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define TWO(x) (1LL<<(x))
inline int gcd(int a, int b) {int r; while (b) {r = a % b; a = b; b = r;} return a;}

// for 64-bit, use mt19937_64
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

// use shuffle instead of random_shuffle
#define random_shuffle askcjaljc

const int MN = 100111;
int a[MN], s[MN], c[MN], nc;
int n, k;

int bit[MN];
void update(int x) {
    for (int u = x; u <= nc; u += u & -u) {
        bit[u]++;
    }
}
int get(int x) {
    int res = 0;
    for (int u = x; u > 0; u -= u & -u) {
        res += bit[u];
    }
    return res;
}

int cnt(int x) {
    memset(bit, 0, sizeof bit);
    int res = 0;
    int id = lower_bound(c+1, c+nc+1, 0) - c;
    update(id);
    FOR(i,1,n) {
        // count how many j: j < i
        // s[i] - s[j] >= x
        // s[i] - x >= s[j]
        // s[j] <= s[i] - x

        int val = upper_bound(c+1, c+nc+1, c[s[i]] - x) - c;
        res += get(val - 1);

        update(s[i]);
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    while (cin >> n >> k) {
        FOR(i,1,n) {
            cin >> a[i];
            s[i] = s[i-1] + a[i];

            c[i] = s[i];
        }
        nc = n;
        c[++nc] = 0;
        sort(c+1, c+nc+1);

        nc = unique(c+1, c+nc+1) - c - 1;
        FOR(i,1,n) {
            s[i] = lower_bound(c+1, c+nc+1, s[i]) - c;
        }

        // binary search
        const int INF = (int) (1e14 + 11);
        int l = -INF, r = INF;
        // find: x: largest, count(sum >= x) >= k
        int res = l;
        while (l <= r) {
            int mid = (l + r) / 2;
            if (cnt(mid) >= k) {
                res = mid;
                l = mid + 1;
            } else {
                r = mid - 1;
            }
        }
        cout << res << endl;
    }
    return 0;
}

