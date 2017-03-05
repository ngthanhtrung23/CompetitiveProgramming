
#include <sstream>
#include <fstream>
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
#define double long double
typedef pair<int, int> II;
#define PI (2 * acos((double)0))
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

int n;
const int MN = 1011;
string a[MN], b[MN], res[MN];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) {
            res[i] = "";
            string u, v; cin >> u >> v;

            a[i] = u.substr(0, 3);
            b[i] = u.substr(0, 2) + v.substr(0, 1);
        }

        FOR(i,1,n) FOR(j,i+1,n) if (a[i] == a[j]) {
            res[i] = b[i];
            res[j] = b[j];
        }
        set<string> all;
        FOR(i,1,n) if (res[i] != "") all.insert(res[i]);

        while (true) {
            bool updated = false;
            FOR(i,1,n) if (res[i] == "") {
                if (all.count(a[i]) || all.count(b[i])) {
                    updated = true;
                    if (all.count(a[i])) res[i] = b[i];
                    else res[i] = a[i];

                    all.insert(res[i]);
                }
            }

            if (!updated) {
                FOR(i,1,n) if (res[i] == "") {
                    updated = true;
                    res[i] = a[i];
                    all.insert(res[i]);
                }
            }
            if (!updated) break;
        }

        bool ok = true;
        FOR(i,1,n) FOR(j,i+1,n) if (res[i] == res[j]) ok = false;
        if (ok) {
            cout << "YES\n";
            FOR(i,1,n) cout << res[i] << '\n';
        }
        else cout << "NO\n";
    }
    return 0;
}
