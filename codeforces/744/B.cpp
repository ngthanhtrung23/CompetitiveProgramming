
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
int GI(ll& x) { return scanf("%lld", &x); }

#define TWO(X) (1LL<<X)
#define CONTAIN(S,X) (S & TWO(X))

set<int> q[22];
int a[22][1011];

int main() {
    int n; cin >> n;
    FOR(i,1,n) {
        REP(bit,10) {
            if (CONTAIN(i,bit)) q[bit].insert(i);
            else q[bit+10].insert(i);
        }
    }

    REP(i,20) {
        if (q[i].empty()) continue;

        cout << SZ(q[i]) << endl;
        for(auto x : q[i]) cout << x << ' '; cout << endl;

        FOR(j,1,n)
            cin >> a[i][j];
    }

    cout << -1 << endl;
    FOR(i,1,n) {
        int res = 1000111000;
        REP(x,20) {
            if (q[x].empty()) continue;
            if (q[x].count(i)) continue;

            res = min(res, a[x][i]);
        }
        cout << res << ' ';
    }
    cout << endl;

    /*
    FOR(i,1,1000) {
        FOR(j,1,1000) if (j != i) {
            bool good = false;
            REP(x,20) if (q[x].count(j)) good = true;
            if (!good) {
                DEBUG(i);
                DEBUG(j);
                assert(0);
            }
        }
    }
    */
}
