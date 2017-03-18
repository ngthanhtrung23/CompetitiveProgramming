
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
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) ((S) & TWO(X))

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(int& x) { return scanf("%lld", &x); }

int a[111];
int f[111][111][111];

struct Pos {
    int x0, x1, x2;

    Pos() {}
    Pos(int x0, int x1, int x2) : x0(x0), x1(x1), x2(x2) {}
};

int go(const Pos& a, const Pos& b) {
    int res = 0;
    if (a.x0 > b.x0) res += a.x0 - b.x0;
    if (a.x1 > b.x1) res += a.x1 - b.x1;
    if (a.x2 > b.x2) res += a.x2 - b.x2;
    return res;
}

void update(int& f, int val) {
    if (f > val) f = val;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);
    int n;
    string s;
    while (cin >> n >> s) {
        vector<Pos> pos[3];
        int n0 = 0, n1 = 0, n2 = 0;

        FOR(i,1,n) {
            char c = s[i-1];
            if (c == 'V') a[i] = 1;
            else if (c == 'K') a[i] = 2;
            else a[i] = 0;

            pos[a[i]].push_back(Pos(n0, n1, n2));

            if (a[i] == 0) ++n0;
            if (a[i] == 1) ++n1;
            if (a[i] == 2) ++n2;
        }

        memset(f, 0x3f, sizeof f);
        const int INF = f[0][0][0];

        f[0][0][0] = 0;
        int res = INF;

        FOR(x0,0,n0) FOR(x1,0,n1) FOR(x2,0,n2) {
            int cur = f[x0][x1][x2];
            if (cur == INF) continue;

            int sum2 = 0;
            FOR(add2,0,n2-x2) {
                int sum1 = 0;
                FOR(add1,0,n1-x1) {
                    if (x0 < n0) {
                        update(f[x0+1][x1+add1][x2+add2],
                                cur + sum1 + sum2
                                + go(pos[0][x0], Pos(x0 + 1, x1+add1, x2+add2)));
                    } else {
                        if (x1+add1 == n1 && x2 + add2 == n2) {
                            update(res, cur + sum1 + sum2);
                        }
                    }

                    if (x1 + add1 < n1)
                        sum1 += go(pos[1][x1+add1], Pos(x0, x1+add1+1, x2+add2));
                }

                if (x2 + add2 < n2) {
                    sum2 += go(pos[2][x2+add2], Pos(x0, x1, x2+add2+1));
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}
