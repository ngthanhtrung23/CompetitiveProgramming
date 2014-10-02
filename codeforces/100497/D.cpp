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

const int MN = 1011;

char a[MN][MN];
int q, n;
int u = 1, v = 1, rot = 0, di = 1, dj = 1;
char tmp[3][3];

void print() {
    REP(i,n) {
        REP(j,n) {
            int ii = u + i * di, jj = v + j * dj;
            if (rot) swap(ii, jj);
            cout << a[ii][jj];
        }
        cout << "\n";
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cin >> n >> q;
    memset(a, '.', sizeof a);

    FOR(i,1,q) {
        string typ;
        cin >> typ;
        if (typ == "REPLACE") {
            int starti, startj; cin >> starti >> startj;
            REP(x,3) REP(y,3) cin >> tmp[x][y];

            REP(i,3) REP(j,3) {
                int ii = u + (i + starti - 1) * di, jj = v + (j + startj - 1) * dj;
                if (rot) swap(ii, jj);
                a[ii][jj] = tmp[i][j];
            }
        } else if (typ == "ROTATE") {
            string dir; cin >> dir;

            int times = (dir == "CW") ? 1 : 3;
            while (times--) {
                rot = 1 - rot;

                swap(u, v);
                v = n - v + 1;

                swap(di, dj);
                dj = -dj;
            }

            // cout << "ROTATE " << dir << endl;
        } else { // MIRROR
            string dir; cin >> dir;
            if ((dir == "VER")) {
                v = n - v + 1;
                dj = -dj;
            } else {
                u = n - u + 1;
                di = -di;
            }

            // cout << "MIRROR " << dir << endl;
        }

        // cout << endl;
    }
        print();
    return 0;
}
