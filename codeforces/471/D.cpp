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

const int MN = 200111;

#define next next_
int a[MN], b[MN], next[MN];
int na, nb;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> na >> nb) {
        FOR(i,1,na) cin >> a[i];
        FOR(i,1,nb) cin >> b[i];

        if (nb == 1) {
            cout << na << endl;
            continue;
        }

        --na; FOR(i,1,na) a[i] = a[i] - a[i+1];
        --nb; FOR(i,1,nb) b[i] = b[i] - b[i+1];

        // PR(a, na);
        // PR(b, nb);

        next[1] = 0; int j = 0;
        FOR(i,2,nb) {
            while (j > 0 && b[i] != b[j+1]) j = next[j];
            if (b[i] == b[j+1]) ++j;
            next[i] = j;
        }

        // PR(next, nb);

        int res = 0; j = 0;
        FOR(i,1,na) {
            while (j > 0 && a[i] != b[j+1]) j = next[j];
            if (a[i] == b[j+1]) ++j;

            if (j == nb) {
                ++res;
                j = next[j];
            }
        }
        cout << res << endl;
    }
    return 0;
}
