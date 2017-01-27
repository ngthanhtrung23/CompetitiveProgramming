
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

const int MN = 200111;

int a[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    while (GI(n) == 1) {
        int k; GI(k);
        FOR(i,1,n) GI(a[i]);
        sort(a+1, a+n+1);

        priority_queue< pair<ll,int> > all;
        all.push(make_pair(-a[1], 1));

        FOR(turn,1,k) {
            auto cur = all.top();
            all.pop();

            if (turn == k) {
                printf("%lld\n", -cur.first);
                break;
            }

            int i = cur.second;

            if (i+1 <= n) {
                // - a[i] + a[i+1]
                all.push(make_pair(cur.first + a[i] - a[i+1], i+1));

                // + a[i+1]
                all.push(make_pair(cur.first - a[i+1], i+1));
            }
        }
    }
}
