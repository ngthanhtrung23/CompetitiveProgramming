
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

const int MN = 7011;

int n;
int a[2][MN], f[2][MN], na[2], bad[2][MN];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    while (cin >> n) {
        REP(turn,2) {
            cin >> na[turn];
            FOR(i,1,na[turn]) cin >> a[turn][i];
        }

        queue<int> qu, qt;
        memset(f, -1, sizeof f);
        qt.push(0); qu.push(0); f[0][0] = 0;
        qt.push(1); qu.push(0); f[1][0] = 0;

        memset(bad, 0, sizeof bad);

        while (!qt.empty()) {
            int t = qt.front(); qt.pop();
            int u = qu.front(); qu.pop();

            FOR(i,1,na[1-t]) {
                int v = u + n - a[1-t][i];
                if (v >= n) v -= n;

                if (f[1-t][v] >= 0) continue;

                if (f[t][u] == 0) {
                    f[1-t][v] = 1;
                    qt.push(1-t);
                    qu.push(v);
                }
                else {
                    ++bad[1-t][v];
                    if (bad[1-t][v] == na[1-t]) {
                        f[1-t][v] = 0;
                        qt.push(1-t);
                        qu.push(v);
                    }
                }
            }
        }

        REP(t,2) {
            FOR(i,1,n-1) {
                if (f[t][i] < 0) cout << "Loop";
                else if (f[t][i] == 0) cout << "Lose";
                else cout << "Win";
                cout << ' ';
            }
            cout << '\n';
        }
    }
    return 0;
}
