
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

int sieve[100111];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    FOR(i,2,1000) if (!sieve[i]) {
        for(int j = i*i; j < 100111; j += i)
            sieve[j] = 1;
    }
    int n;
    while (cin >> n) {
        if (n <= 2) puts("1");
        else puts("2");
        FOR(i,2,n+1) {
            if (!sieve[i]) printf("1 ");
            else printf("2 ");
        }
        puts("");
    }
}
