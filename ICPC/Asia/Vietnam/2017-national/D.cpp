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

int n_milk, milk[10111];
int n_topping, topping[10111];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    cin >> n_milk;
    assert(1 <= n_milk && n_milk <= 1000);

    FOR(i,1,n_milk) {
        cin >> milk[i];
        assert(1 <= milk[i] && milk[i] <= 1000);
    }

    cin >> n_topping;
    assert(1 <= n_topping && n_topping <= 1000);
    FOR(i,1,n_topping) {
        cin >> topping[i];
        assert(1 <= topping[i] && topping[i] <= 1000);
    }

    int min_cost = 1000111000111LL;
    FOR(i,1,n_milk) {
        int k; cin >> k;
        FOR(j,1,k) {
            int id;
            cin >> id;
            min_cost = min(min_cost, milk[i] + topping[id]);
        }
    }
    assert(min_cost > 0);

    int X; cin >> X;
    assert(0 <= X && X <= 1000000000);
    cout << max(X / min_cost - 1, 0LL) << endl;
    return 0;
}
