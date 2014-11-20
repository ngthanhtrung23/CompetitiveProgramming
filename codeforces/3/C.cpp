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

#define F0R(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define F0RD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; F0R(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

char a[5][5];

int count(char c) {
    int res = 0;
    F0R(i,1,3) F0R(j,1,3) if (a[i][j] == c) ++res;
    return res;
}

bool win(char c) {
    F0R(i,1,3) {
        if (a[i][1] == c && a[i][2] == c && a[i][3] == c) return true;
        if (a[1][i] == c && a[2][i] == c && a[3][i] == c) return true;
    }
    if (a[1][1] == c && a[2][2] == c && a[3][3] == c) return true;
    if (a[1][3] == c && a[2][2] == c && a[3][1] == c) return true;
    return false;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> a[1][1]) {
        F0R(i,1,3) F0R(j,1,3) if (i > 1 || j > 1) cin >> a[i][j];

        int nx = count('X');
        int no = count('0');

        if (!(nx == no || nx == no + 1)) cout << "illegal" << endl;
        else {
            bool winx = win('X');
            bool wino = win('0');

            if (winx && wino) cout << "illegal" << endl;
            else if (winx && nx != no + 1) cout << "illegal" << endl;
            else if (wino && nx != no) cout << "illegal" << endl;
            else if (winx) cout << "the first player won" << endl;
            else if (wino) cout << "the second player won" << endl;
            else if (nx + no == 9) cout << "draw" << endl;
            else if (nx == no) cout << "first" << endl;
            else cout << "second" << endl;
        }
    }
    return 0;
}

