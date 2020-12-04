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
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { cerr << #X << " = " << (X) << endl; }
#define PR(A, n) { cerr << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

int rand16() {
    return rand() & (TWO(16) - 1);
}
int my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

const int MN = 100111;
int n, m, k, sa, sb;
vector<int> ke[MN];
int val[MN], f[MN];
const int INF = 1000111000111000111LL;

int get(int u) {
    if (f[u] > -INF) return f[u];

    if (ke[u].empty()) return f[u] = 0;

    for (int v : ke[u]) {
        f[u] = max(f[u], val[v] + get(v));
    }

    return f[u];
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    cin >> n >> m >> k >> sa >> sb;
    FOR(i,1,m) {
        int u, v;
        cin >> u >> v;
        ke[u].push_back(v);
    }
    FOR(i,1,n) {
        string typ; cin >> typ;
        if (typ[0] == 'S') {
            cin >> val[i];
        } else if (typ[0] == 'T') {
            cin >> val[i];
            val[i] = -val[i];
        } else {
            assert(typ[0] == 'P');
            int x, y; cin >> x >> y;
        }
    }
    FOR(i,1,n) f[i] = -INF;
    cout << get(sa) << ' ' << get(sb) << endl;
    return 0;
}
