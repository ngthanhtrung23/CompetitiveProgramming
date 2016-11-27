
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
int GI(int& x) { return scanf("%d", &x); }

int n, k;
bitset<4011> a[2011];
int eu[500111], ev[500111];

int main() {
    while (GI(n) == 1 && GI(k) == 1) {
        REP(i,n) a[i].reset();

        FOR(i,1,k) {
            int u, v; GI(u); GI(v); --u; --v;
            a[u].set(v);
            eu[i] = u;
            ev[i] = v;
        }
        REP(i,n) a[i].set(n+i);

        REP(i,n) {
            int j = i;
            while (!a[j].test(i)) ++j;

            swap(a[i], a[j]);

            REP(k,n) if (k != i && a[k].test(i))
                a[k] ^= a[i];
        }

        FOR(i,1,k) {
            puts(a[ev[i]].test(n + eu[i]) ? "NO" : "YES");
        }
    }
}
