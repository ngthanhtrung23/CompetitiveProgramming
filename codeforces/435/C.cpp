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

int n, a[1011];
char board[2011][2011];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        memset(board, ' ', sizeof board);

        int i = 1001, j = 0;
        char cur = '/';
        FOR(u,1,n) {
            while (a[u]) {
                ++j;
                board[i][j] = cur;
                --a[u];
                if (a[u]) {
                    if (cur == '/') --i;
                    else ++i;
                }
            }
            if (cur == '/') cur = '\\';
            else cur = '/';
        }
        int width = j;
        FOR(i,0,2010) {
            int ln = 0;
            FOR(j,1,2010) if (board[i][j] != ' ') {
                ln = j;
            }
            if (ln == 0) continue;

            FOR(j,1,width) cout << (char) board[i][j];
            cout << endl;
        }
    }
    return 0;
}
