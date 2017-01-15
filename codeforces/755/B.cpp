
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
int GI(int& x) { return scanf("%lld", &x); }

#undef int
int main() {
#define int long long
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n, m;
    while (cin >> n >> m) {
        set<string> a, b, both;
        string s;
        FOR(i,1,n) {
            cin >> s;
            a.insert(s);
        }
        FOR(i,1,m) {
            cin >> s;
            b.insert(s);
            if (a.count(s)) both.insert(s);
        }

        int good_a = SZ(a) - SZ(both);
        int good_b = SZ(b) - SZ(both);
        int good_both = SZ(both);

        while (true) {
            // a
            if (good_both) --good_both;
            else if (good_a) --good_a;
            else {
                cout << "NO" << endl;
                break;
            }
            // b
            if (good_both) --good_both;
            else if (good_b) --good_b;
            else {
                cout << "YES" << endl;
                break;
            }
        }
    }
}
