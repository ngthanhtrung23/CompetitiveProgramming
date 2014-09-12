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

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

map<int, set<int> > hasS, hasX;
set<int> ignored;

bool itemLockedS(int item, int trid) {
    if (!hasS.count(item)) return false;
    for(__typeof(hasS[item].begin()) it = hasS[item].begin(); it != hasS[item].end(); ++it) {
        if (*it != trid) return true;
    }
    return false;
}
bool itemLockedX(int item, int trid) {
    if (!hasX.count(item)) return false;
    for(__typeof(hasX[item].begin()) it = hasX[item].begin(); it != hasX[item].end(); ++it) {
        if (*it != trid) return true;
    }
    return false;
}

int main() {
    char typ;
    while (cin >> typ && typ != '#') {
        int trid, item;
        cin >> trid >> item;

        if (ignored.count(trid)) {
            puts("IGNORED");
            continue;
        }

        if (typ == 'S') {
            if (itemLockedX(item, trid)) {
                puts("DENIED");
                ignored.insert(trid);
            } else {
                puts("GRANTED");
                hasS[item].insert(trid);
            }
        } else {
            if (itemLockedX(item, trid) || itemLockedS(item, trid)) {
                puts("DENIED");
                ignored.insert(trid);
            } else {
                puts("GRANTED");
                hasX[item].insert(trid);
            }
        }
    }
}