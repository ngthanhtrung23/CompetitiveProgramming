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

int hp[5], atk[5], def[5];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> hp[0] >> atk[0] >> def[0]) {
        cin >> hp[1] >> atk[1] >> def[1];
        int h, a, d, res = 1000111000;
        cin >> h >> a >> d;

        for(atk[2] = atk[0]; atk[2] <= 200; ++atk[2])
        for(def[2] = def[0]; def[2] <= 100; ++def[2]) {
            if (atk[2] <= def[1]) continue;
            int hp1 = hp[1], turn = 0;
            while (hp1 > 0) {
                ++turn;
                hp1 -= max(0, atk[2]-def[1]);
            }
            int each = max(0, atk[1]-def[2]);
            hp[2] = each * turn + 1;
            if (hp[2] < hp[0]) hp[2] = hp[0];

            res = min(res,
                    (hp[2] - hp[0]) * h +
                    (atk[2] - atk[0]) * a +
                    (def[2] - def[0]) * d);
        }

        cout << res << endl;
    }
    return 0;
}
