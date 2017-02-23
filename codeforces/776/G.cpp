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

int hexDec(char c) {
    if (c >= 'a' && c <= 'z') return c - 'a' + 10;
    return c - '0';
}

vector<char> digits;
int f[20][2][2];
int bit[66];

void expand(string s) {
    int x = 0;
    for(char c : s)
        x = x*16 + hexDec(c);

    memset(bit, 0, sizeof bit);
    REP(i,60) bit[i] = x % 2, x /= 2;
}

int cache_bit[22][22][66];

int get(string s, bool needLower) {
    int res = 0;
    while (SZ(s) < 15) s = '0' + s;

    expand(s);

    REP(ln,16) {
        char maxDigit = digits[ln];

        memset(f, 0, sizeof f);
        f[0][0][0] = 1;

        REP(i,15) REP(lower,2) REP(has,2) {
            int cur = f[i][lower][has];
            if (!cur) continue;

            REP(value,ln+1) {
                if (!lower && digits[value] > s[i]) continue;
                if (cache_bit[i][value][ln] == 0) continue;
//                if (!can[i][value]) continue;

                int lower2 = lower; if (digits[value] < s[i]) lower2 = 1;
                int has2 = has; if (value == ln) has2 = 1;

                f[i+1][lower2][has2] += cur;
            }
        }

        res += f[15][1][1];
        if (!needLower) res += f[15][0][1];
    }
    return res;
}

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9);

    FOR(c,'0','9') digits.push_back(c);
    FOR(c,'a','z') digits.push_back(c);

    REP(i,15) {
        REP(index,16) {
            string s2 = "";
            REP(turn,15) {
                if (turn == i) s2 += digits[index];
                else s2 += 'f';
            }

            expand(s2);
            REP(pos,60) cache_bit[i][index][pos] = bit[pos];
            //can[i][index] = (bit[ln] == 1);
        }
    }

    int q; while (cin >> q) {
        while (q--) {
            string a, b;
            cin >> a >> b;
            int res = get(b, false);

            res -= get(a, true);
            cout << res << '\n';
        }
        cout << endl;
    }
}
