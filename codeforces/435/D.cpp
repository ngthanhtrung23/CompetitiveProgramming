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
char a[411][411], b[411][411];
int ngang[411][411], cheo[411][411];

void rotate() {
    FOR(i,1,m) FOR(j,1,n) b[i][j] = a[i][j];
    memset(a, ' ', sizeof a);
    FOR(i,1,n) FOR(j,1,m) a[i][j] = b[j][n-i+1];
    swap(m, n);

    memset(ngang, 0, sizeof ngang);
    memset(cheo, 0, sizeof cheo);
    FOR(i,1,m) {
        FOR(j,1,n) {
            ngang[i][j] = ngang[i][j-1] + a[i][j] - '0';
            cheo[i][j] = cheo[i-1][j+1] + a[i][j] - '0';
        }
    }
}

int solve() {
    int res = 0;
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '0') {
        int i2 = i, j2 = j+1;
        int i3 = i+1, j3 = j;
        while (a[i2][j2] == '0' && a[i3][j3] == '0') {
            if (cheo[i3][j3] - cheo[i2][j2] == 0) ++res;
            ++j2;
            ++i3;
        }

        i2 = i+1, j2 = j-1;
        i3 = i+1, j3 = j+1;
        while (a[i2][j2] == '0' && a[i3][j3] == '0') {
            if (ngang[i3][j3] - ngang[i2][j2] == 0) ++res;
            ++i2; --j2;
            ++i3; ++j3;
        }
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m >> n) {
        memset(a, ' ', sizeof a);
        FOR(i,1,m) FOR(j,1,n) cin >> a[i][j];
        long long res = 0;
        REP(turn,4) {
            rotate();
            res += solve();
        }
        cout << res << endl;
    }
    return 0;
}
