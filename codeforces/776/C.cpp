
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

int n, k;
int a[100111], s[100111];
int pk[111], npk;

void init() {
    npk = 0;

    if (k == 1) {
        pk[npk++] = 1;
        return ;
    }
    if (k == -1) {
        pk[npk++] = 1;
        pk[npk++] = -1;
        return ;
    }

    bool neg = false;
    if (k < 0) neg = true, k = -k;

    int cur = 1;
    FOR(i,0,64) {
        pk[npk++] = cur;
        cur *= k;

        if (cur < 0 || cur > 1000111000111000) break;
    }

    if (neg) {
        k = -k;
        for(int i = 1; i < npk; i += 2)
            pk[i] = -pk[i];
    }
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (GI(n) == 1 && GI(k) == 1) {
        init();
        FOR(i,1,n) {
            GI(a[i]);
            s[i] = s[i-1] + a[i];
        }

        map<int,int> cnt;
        cnt[0] = 1;
        int res = 0;
        FOR(i,1,n) {
            REP(ipk,npk) {
                int need = pk[ipk];
                res += cnt[s[i] - need];
            }
            cnt[s[i]]++;
        }
        cout << res << '\n';
    }
}
