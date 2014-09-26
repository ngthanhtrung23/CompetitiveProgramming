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

int a[11];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> a[1]) {
        FOR(i,2,6) cin >> a[i];
        sort(a+1, a+7);

        bool ok = false;
        FOR(i,1,3) if (a[i] == a[i+1] && a[i] == a[i+2] && a[i] == a[i+3]) {
            int u = -1, v = -1;
            FOR(x,1,6)
                if (x < i || x > i+3) {
                    if (u < 0) u = a[x];
                    else v = a[x];
                }

            ok = true;
            if (u == v) {
                cout << "Elephant";
            } else cout << "Bear";
            break;
        }

        if (!ok) cout << "Alien";
        cout << endl;
    }
    return 0;
}
