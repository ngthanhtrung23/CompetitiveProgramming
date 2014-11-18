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

#define ONE { cout << "Team 1" << endl; continue; }
#define TWO { cout << "Team 2" << endl; continue; }

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int def1, def2, def3, def4;
    int att1, att2, att3, att4;
    while (cin >> def1 >> att1 >> def2 >> att2 >> def3 >> att3 >> def4 >> att4) {
        // Team 1 wins?
        if ((def1 > att3 && att2 > def4) && (def1 > att4 && att2 > def3)) ONE;
        if ((def2 > att3 && att1 > def4) && (def2 > att4 && att1 > def3)) ONE;

        // Team 2 wins?
        if ((def3 > att1 && att4 > def2) || (def4 > att1 && att3 > def2))
            if ((def3 > att2 && att4 > def1) || (def4 > att2 && att3 > def1))
                TWO;

        cout << "Draw" << endl;
    }
    return 0;
}
