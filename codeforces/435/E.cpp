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

int m, n;
char a[1011][1011], res[1011][1011];

bool row(int i, char x, char y) {
    FOR(j,1,n) {
        if (a[i][j] != '0') {
            if (j % 2 == 1 && a[i][j] != x) return false;
            if (j % 2 == 0 && a[i][j] != y) return false;
        }
    }
    return true;
}

bool col(int j, char x, char y) {
    FOR(i,1,m) {
        if (a[i][j] != '0') {
            if (i % 2 == 1 && a[i][j] != x) return false;
            if (i % 2 == 0 && a[i][j] != y) return false;
        }
    }
    return true;
}

void print() {
    FOR(i,1,m) {
        FOR(j,1,n) cout << res[i][j];
        cout << "\n";
    }
}

void solve() {
    for(char x = '1'; x <= '4'; ++x) for(char y = x + 1; y <= '4'; ++y) {
        char z = '1'; while (z == x || z == y) ++z;
        char t = '1'; while (t == x || t == y || t == z) ++t;

        bool ok = true;
        FOR(i,1,m) {
            char one, two;
            if (i % 2 == 1) one = x, two = y;
            else one = z, two = t;
            if (!row(i, one, two) && !row(i, two, one)) {
                ok = false;
                break;
            }
        }
        if (ok) {
            FOR(i,1,m) {
                char one, two;
                if (i % 2 == 1) one = x, two = y;
                else one = z, two = t;

                if (!row(i, one, two)) swap(one, two);
                FOR(j,1,n) {
                    if (j % 2 == 1) res[i][j] = one;
                    else res[i][j] = two;
                }
            }
            print();
            return ;
        }

        ok = true;
        FOR(j,1,n) {
            char one, two;
            if (j % 2 == 1) one = x, two = y;
            else one = z, two = t;
            if (!col(j, one, two) && !col(j, two, one)) {
                ok = false;
                break;
            }
        }
        if (ok) {
            FOR(j,1,n) {
                char one, two;
                if (j % 2 == 1) one = x, two = y;
                else one = z, two = t;

                if (!col(j, one, two)) swap(one, two);
                FOR(i,1,m) {
                    if (i % 2 == 1) res[i][j] = one;
                    else res[i][j] = two;
                }
            }
            print();
            return ;
        }
    }
    cout << 0 << endl;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m >> n) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        solve();
    }
    return 0;
}
