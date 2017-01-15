
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

int main() {
    int n, k;
    while (cin >> n >> k) {
        if (n == 2 || n == 3) {
            // either graph is not connected --> min(dr, dw) = -1
            puts("-1");
            continue;
        }

        if (k > 3 || k == 1) {
            puts("-1");
            continue;
        }

        if (k == 2) {
            if (n == 4) {
                puts("-1");
                continue;
            }
            else {
                printf("%d\n", n-1);
                FOR(i,2,n) printf("%d %d\n", i-1, i);
                continue;
            }
        }
        if (k == 3) {
            if (n == 4) {
                puts("3");
                puts("1 2");
                puts("2 3");
                puts("3 4");
            }
            else {
                vector< pair<int,int> > edges;
                edges.emplace_back(1, 2);
                edges.emplace_back(2, 3);
                edges.emplace_back(3, 1);
                FOR(i,4,n) {
                    if (i % 2 == 0) edges.emplace_back(i, 2);
                    else edges.emplace_back(i, 3);
                }
                printf("%d\n", SZ(edges));
                for(auto p : edges)
                    printf("%d %d\n", p.first, p.second);
            }
        }
    }
}
