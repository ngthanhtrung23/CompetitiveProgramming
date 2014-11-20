#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 1011;
const int oo = MN * MN;
const int MOD = 1000000007;
int n;
char a[MN][MN];
pair<int,int> f[MN][MN], g[MN][MN];

void update(pair<int,int> &f, pair<int,int> val, char c) {
    int now = val.first + ((c == 'C') ? 1 : 0);
    if (f.first < now) {
        f.first = now;
        f.second = val.second;
    }
    else if (f.first == now) {
        f.second = (f.second + val.second) % MOD;
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];
        FOR(i,0,n+1) FOR(j,0,n+1) f[i][j] = g[i][j] = make_pair(-oo, 0);

        FOR(i,1,n) FOR(j,1,n) {
            if (i == 1 && j == 1) {
                if (a[i][j] == 'C') f[i][j] = make_pair(1, 1);
                else f[i][j] = make_pair(0, 1);
            }
            else {
                update(f[i][j], f[i-1][j], a[i][j]);
                update(f[i][j], f[i][j-1], a[i][j]);
            }
        }
        FORD(i,n,1) FORD(j,n,1) {
            if (i == n && j == n) {
                if (a[i][j] == 'C') g[i][j] = make_pair(1, 1);
                else g[i][j] = make_pair(0, 1);
            }
            else {
                update(g[i][j], g[i+1][j], a[i][j]);
                update(g[i][j], g[i][j+1], a[i][j]);
            }
        }

        int q; cin >> q;
        while (q--) {
            int r1, c1, r2, c2; cin >> r1 >> c1 >> r2 >> c2;
            ++r1; ++c1; ++r2; ++c2;

            if (r1 > r2) swap(r1, r2);
            if (c1 > c2) swap(c1, c2);

            pair<int,int> res = make_pair(0, 0);
            FOR(i,r2+1,n) {
                pair<int,int> cur = make_pair(f[i][c1-1].first + g[i][c1].first,
                        f[i][c1-1].second * (long long) g[i][c1].second % MOD);
                update(res, cur, 0);
            }
            FOR(j,c2+1,n) {
                pair<int,int> cur = make_pair(f[r1-1][j].first + g[r1][j].first,
                        f[r1-1][j].second * (long long) g[r1][j].second % MOD);
                update(res, cur, 0);
            }
            cout << res.first << ' ' << res.second << "\n";
        }
    }
    return 0;
}
