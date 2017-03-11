
#include <sstream>
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
#include <stack>
#include <map>
#include <string>
#include <queue>
#include <bitset>
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _b = (b); i <= _b; ++i)
#define FORD(i, a, b) for (int i = (a), _b = (b); i >= _b; --i)
#define REP(i, a) for (int i = 0, _a = (a); i < _a; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define ld long double
typedef pair<int, int> II;
#define PI (2 * acos((ld)0))
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define y0 u9cqu3jioajc

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 4000111;
const int MOD = 1e9 + 7;

int O[MN], R[MN];
int n;
int f[MN];

int next(int i) {
    if (i == n) return 1;
    return i+1;
}
int prev(int i) {
    if (i == 1) return n;
    return i-1;
}

void dijkstra() {
    f[n+1] = 0;
    set< pair<int,int> > all;
    FOR(i,1,n) {
        f[i] = R[i];
        all.insert(make_pair(f[i], i));
    }

    while (!all.empty()) {
        auto p = *all.begin();
        all.erase(all.begin());
        int l = p.first;
        int u = p.second;

        int v = prev(u);
        if (f[v] > f[u] + O[v]) {
            f[v] = f[u] + O[v];
            all.insert(make_pair(f[v], v));
        }

        v = next(u);
        if (f[v] > f[u] + O[u]) {
            f[v] = f[u] + O[u];
            all.insert(make_pair(f[v], v));
        }
    }
}

int sumO[MN], sumf[MN], sumSO[MN];
int v1[MN], v2[MN];

int goRound(int u, int v) {
    assert(u != v);

    v = prev(v);
    if (v < u) v += n;

    return sumO[v] - sumO[u-1];
}

int isV1(int i, int j) {
    if (j == i) return false;

    int xuoi = goRound(i, j);
    int nguoc = goRound(j, i);
    int tam = f[i] + f[j];

    return xuoi <= nguoc && xuoi < tam;
}

int isV2(int i, int j) {
    if (j == i) return false;

    int xuoi = goRound(i, j);
    int nguoc = goRound(j, i);
    int tam = f[i] + f[j];

    return nguoc < xuoi && nguoc < tam;
}

int count(int i, int j) {
    if (j < i) j += n;
    return j - i + 1;
}

int solve() {
    // calculate f
    dijkstra();

    FOR(i,1,n) {
        O[i] = min(O[i], f[i] + f[next(i)]);
    }

    // init DP
    FOR(i,1,n+n+n) O[i+n] = O[i];
    FOR(i,1,n+n+n) f[i+n] = f[i];

    FOR(i,1,4*n) sumO[i] = sumO[i-1] + O[i];
    FOR(i,1,4*n) sumf[i] = sumf[i-1] + f[i];

    FOR(i,1,4*n) sumSO[i] = sumSO[i-1] + sumO[i];

    // calculate v1[1]
    v1[1] = v2[1] = 1;
    FOR(j,2,n) {
        if (isV1(1, j)) v1[1] = j;
        else break;
    }
    // calculate v2[1]
    FORD(j,n,2) {
        if (isV2(1, j)) v2[1] = j;
        else break;
    }

    // calculate v1
    FOR(i,2,n) {
        if (v1[prev(i)] == prev(i)) v1[i] = i;
        else v1[i] = v1[prev(i)];

        while (true) {
            int j = next(v1[i]);

            if (isV1(i, j)) v1[i] = j;
            else break;
        }
    }

    // calculate v2
    FORD(i,n,1) {
        if (v2[next(i)] == next(i)) v2[i] = i;
        else v2[i] = v2[next(i)];
        while (true) {
            int j = prev(v2[i]);

            if (isV2(i, j)) v2[i] = j;
            else break;
        }
    }

    int res = 0;

    FOR(i,1,n) {
        int cnt = 0;
        // next(i) to v1[i]
        if (v1[i] != i) {
            int u = i;
            int l = next(i);
            int r = v1[i];
            if (l < u) l += n;
            while (r < l) r += n;

            assert(u <= l && l <= r);

            if (l == 1) {
                u += n;
                l += n;
                r += n;
            }

            cnt += r - l + 1;

            res += sumSO[r-1] - sumSO[l-2];
            res -= count(l, r) * sumO[u-1];
        }

        // v2[i] to prev(i)
        if (v2[i] != i) {
            int l = v2[i];
            int r = prev(i);
            int u = i;
            if (r < l) r += n;
            while (u < r) u += n;

            assert(l <= r && r <= u);

            if (l == 1) {
                l += n; r += n;
                u += n;
            }

            cnt += r - l + 1;
            res += sumO[u-1] * count(l, r);
            res -= sumSO[r-1] - sumSO[l-2];
        }

        // through center
        int l = next(v1[i]);
        if (l == v2[i]) continue;

        int r = prev(v2[i]);
        if (r < l) r += n;

        res += sumf[r] - sumf[l-1];
        res += count(l, r) * f[i];
    }

    res /= 2;

    FOR(i,1,n) res += f[i];
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int ntest; cin >> ntest;
    FOR(test,1,ntest) {
        cin >> n;
        int Ao, Bo, Co, Do;
        cin >> O[1] >> Ao >> Bo >> Co >> Do;
        FOR(i,2,n) O[i] = (Ao * O[i-1] + Bo) % Co + Do;

        int Ar, Br, Cr, Dr;
        cin >> R[1] >> Ar >> Br >> Cr >> Dr;
        FOR(i,2,n) R[i] = (Ar * R[i-1] + Br) % Cr + Dr;

        cout << "Case #" << test << ": " << solve() % MOD << endl;
    }
}
