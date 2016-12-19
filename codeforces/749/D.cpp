
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
const int BIG = 500;

int a[MN], b[MN];
vector<int> pos[MN];
set< pair<int,int> > ln;
int n;

int getSmall(const set<int>& bad) {
    for(auto it = ln.begin(); it != ln.end(); ++it) {
        if (!bad.count(it->second)) return it->second;
    }
    return 0;
}

int getBig(const set<int>& bad) {
    int res = n;
    while (bad.count(a[res])) --res;
    return a[res];
}

int main() {
    while (GI(n) == 1) {
        ++n;
        FOR(i,1,n) pos[i].clear();

        a[1] = b[1] = 0;
        FOR(i,2,n) {
            GI(a[i]);
            GI(b[i]);
        }

        ln.clear();
        FOR(i,1,n) {
            pos[a[i]].push_back(i);
        }
        FOR(i,0,n) if (!pos[i].empty()) ln.insert(make_pair(-pos[i].back(), i));

        int q; GI(q);
        while (q--) {
            int k; GI(k);
            set<int> bad;
            FOR(i,1,k) {
                int u; GI(u); bad.insert(u);
            }

            int res, res2;
            if (k <= BIG) {
                res = getSmall(bad);
                if (res) {
                    bad.insert(res);
                }
                res2 = getSmall(bad);
            }
            else {
                res = getBig(bad);
                if (res) bad.insert(res);
                res2 = getBig(bad);
            }
            int x = *lower_bound(pos[res].begin(), pos[res].end(), pos[res2].back());
            printf("%d %d\n", a[x], b[x]);
        }
        puts("");
    }
}
