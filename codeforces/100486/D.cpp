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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 2011;

int m, n;
int a[MN][MN], fNgang[MN][MN], fCheo[MN][MN], b[MN][MN];
int doc[MN][MN], ngang[MN][MN];

void rotate() {
    FOR(i,1,m) FOR(j,1,n) b[i][j] = a[i][j];

    swap(m, n);
    FOR(i,1,m) FOR(j,1,n) a[i][n - j + 1] = b[j][i];
}

#define BOARD(a) { cout << #a << endl; FOR(i,1,m) { FOR(j,1,n) cout << a[i][j] << ' '; cout << endl; } }

void init() {
    FORD(i,m,1) FOR(j,1,n) {
        if (i == m || a[i][j] != a[i+1][j]) doc[i][j] = 1;
        else doc[i][j] = doc[i+1][j] + 1;
    }
    // BOARD(doc);

    FOR(i,1,m-1) FORD(j,n,1) {
        if (j == n) {
            if (a[i][j] == a[i+1][j]) ngang[i][j] = 1;
            else ngang[i][j] = 0;
        } else {
            if (a[i][j] == a[i+1][j]) ngang[i][j] = 1 + ngang[i][j+1];
            else ngang[i][j] = 0;
        }
    }

    // FOR(i,1,m-1) FORD(j,n,2) {
    //     if (j == n) {
    //         if (a[i][j] == a[i+1][j-1]) ngang[1][i][j] = 1;
    //         else ngang[1][i][j] = 0;
    //     } else {
    //         if (a[i][j] == a[i+1][j-1]) ngang[1][i][j] = 1 + ngang[1][i][j+1];
    //         else ngang[1][i][j] = 0;
    //     }
    // }

    // BOARD(ngang);
    // BOARD(ngang[1]);
}

int solve() {
    // BOARD(a);
    init();

    int res = 0;

    // fNgang
    FORD(i,m,1) FORD(j,n,1) {
        if (i == m || j == n) fNgang[i][j] = 1;
        else {
            if (a[i][j] != a[i+1][j]) fNgang[i][j] = 1;
            else if (a[i][j+1] != a[i+1][j+1]) fNgang[i][j] = 1;
            else if (i >= m-1 || j >= n-1) fNgang[i][j] = 2;
            else {
                if (a[i][j] - a[i][j+1] != a[i][j+1] - a[i][j+2]) fNgang[i][j] = 2;
                else {
                    fNgang[i][j] = min(fNgang[i+1][j+1] + 1, min(doc[i][j], ngang[i][j]));
                }
            }
        }
        res = max(res, fNgang[i][j]);
    }
    // BOARD(fNgang);

    // fCheo
    FORD(i,m,1) FORD(j,n,1) {
        if (i == m || j == n) fCheo[i][j] = 1;
        else {
            if (a[i+1][j] != a[i][j+1]) fCheo[i][j] = 1;
            else if (a[i][j] - a[i][j+1] != a[i][j+1] - a[i+1][j+1]) fCheo[i][j] = 1;
            else if (i >= m-1 || j >= n-1) fCheo[i][j] = 2;
            else {
                fCheo[i][j] = min(fCheo[i+1][j+1], min(fCheo[i+1][j], fCheo[i][j+1])) + 1;
            }
        }

        res = max(res, fCheo[i][j]);
    }
    // BOARD(fCheo);
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> m >> n && m) {
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];

        int res = solve();
        rotate();
        res = max(res, solve());

        // DEBUG(res);

        cout << res * res << endl;
    }
    return 0;
}
