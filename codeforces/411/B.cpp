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

int nCore, nCell, nInstr;
int x[111][111];
int lockedCell[111], lockedCore[111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> nCore >> nInstr >> nCell) {
        memset(lockedCore, 0, sizeof lockedCore);
        memset(lockedCell, 0, sizeof lockedCell);

        FOR(i,1,nCore) FOR(j,1,nInstr) cin >> x[i][j];
        FOR(time,1,nInstr) {
            FOR(i,1,nCore) FOR(j,i+1,nCore)
                if (!lockedCore[i] || lockedCore[i] == time)
                if (!lockedCore[j] || lockedCore[j] == time)
                if (x[i][time] == x[j][time] && x[i][time]) {
                    if (!lockedCore[i]) lockedCore[i] = time;
                    if (!lockedCore[j]) lockedCore[j] = time;
                    if (!lockedCell[x[i][time]]) lockedCell[x[i][time]] = 1;
                }
            FOR(i,1,nCore)
                if (!lockedCore[i])
                if (lockedCell[x[i][time]])
                    lockedCore[i] = time;
        }
        FOR(i,1,nCore) cout << lockedCore[i] << endl;
    }
    return 0;
}

