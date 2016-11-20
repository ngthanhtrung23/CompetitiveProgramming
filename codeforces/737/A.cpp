#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <queue>
#include <bitset>
#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
using namespace std;

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(ll& x) { return scanf("%lld", &x); }

const int MN = 200111;

int n, s, t, k;
int g[MN];
pair<int,int> cars[MN], good[MN];
int dist[MN];

int check(int cap) {
    int res = 0;
    FOR(i,1,k) {
        int D = dist[i];
        if (cap < D) return 1000111000111LL;
        if (cap >= 2*D) res += D;
        else res += 3*D - cap;
    }
    return res;
}

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1) {
        GI(k); GI(s); GI(t);
        FOR(i,1,n) {
            GI(cars[i].first);
            GI(cars[i].second);
            cars[i].second = -cars[i].second;
        }
        sort(cars+1, cars+n+1);
        FOR(i,1,n) cars[i].second = -cars[i].second;

        int nGood = 0;
        int bestCap = -1;
        FOR(i,1,n) {
            if (cars[i].second > bestCap) {
                bestCap = cars[i].second;
                good[++nGood] = cars[i];
            }
        }
//        FOR(i,1,nGood) cout << good[i].first << ' ' << good[i].second << endl;

        FOR(i,1,k) GI(g[i]);
        sort(g+1, g+k+1);
        g[++k] = s;
        FOR(i,1,k) dist[i] = g[i] - g[i-1];
//        PR(dist, k);

        int l = 1, r = nGood, res = -1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int can = check(good[mid].second);
            if (can <= t) {
                res = mid;
                r = mid - 1;
            }
            else l = mid + 1;
        }
        if (res < 0) cout << res << endl;
        else cout << good[res].first << endl;
    }
}
