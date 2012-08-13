#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

const double PI = acos(-1.0);

char a[11][11];

int count(char c) {
    int res = 0;
    REP(i,3) REP(j,3)
        if (a[i][j] == c) ++res;
    return res;
}

bool check(char c) {
    REP(i,3) {
        if (a[i][0] == c && a[i][1] == c && a[i][2] == c) return true;
        if (a[0][i] == c && a[1][i] == c && a[2][i] == c) return true;
    }
    if (a[0][0] == c && a[1][1] == c && a[2][2] == c) return true;
    if (a[2][0] == c && a[1][1] == c && a[0][2] == c) return true;
    return false;
}

int main() {
    while (gets(a[0])) {
        gets(a[1]); gets(a[2]);

        int nx = count('X');
        int no = count('0');
        int turn;

        if (nx == no+1) turn = 0;
        else if (nx == no) turn = 1;
        else {
            puts("illegal");
            continue;
        }

        if (check('X') && check('0')) {
            puts("illegal");
            continue;
        }

        if (check('X')) {
            if (turn == 1) puts("illegal");
            else puts("the first player won");
            continue;
        }
        if (check('0')) {
            if (turn == 0) puts("illegal");
            else puts("the second player won");
            continue;
        }
        if (count('.') == 0) {
            puts("draw");
            continue;
        }
        if (turn == 0) puts("second");
        else puts("first");
    }
    return 0;
}
