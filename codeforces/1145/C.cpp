
/*
#pragma GCC optimize("O3")
#ifdef ONLINE_JUDGE
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif
#pragma GCC optimize("unroll-loops")
*/
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
// On CF, GNU C++ seems to have some precision issues with long double?
// #define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define stat akjcjalsjcjalscj
#define hash ajkscjlsjclajsc
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (((S) >> (X)) & 1)

long long rand16() {
    return rand() & (TWO(16) - 1);
}
long long my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(long long& x) { return scanf("%lld", &x); }

int f(int n) {
    if (n == 0) return 15;
    if (n == 1) return 14;
    if (n == 2) return 12;
    if (n == 3) return 13;
    if (n == 4) return 8;
    if (n == 5) return 9;
    if (n == 6) return 10;
    if (n == 7) return 11;
    if (n == 8) return 0;
    if (n == 9) return 1;
    if (n == 10) return 2;
    if (n == 11) return 3;
    if (n == 12) return 4;
    if (n == 13) return 5;
    if (n == 14) return 6;
    if (n == 15) return 7;

    int SZ = n * 1000111;
    vector<int> a(SZ);
    REP(t,SZ) a[t] = a[t - 1] + a[t / 2] + (n * n * my_rand()) % 123;
    int sum = 0;
    REP(t,SZ) sum += a[t] + a[t / 2];
    return sum;
}

int32_t main() {
    int n; cin >> n;
    cout << f(n) << endl;
    return 0;
}
