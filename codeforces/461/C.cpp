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

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 100111;
int n, q;
int bit[MN];

#define _(X) ((X) & (-(X)))
void update(int u, int val) {
    while (u < MN) {
        bit[u] += val;
        u += _(u);
    }
}
int get(int u) {
    int res = 0;
    while (u > 0) {
        res += bit[u];
        u -= _(u);
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> q) {
        memset(bit, 0, sizeof bit);
        FOR(i,1,n) update(i, 1);

        int from = 0, to = n;
        bool reversed = false;
        while (q--) {
            int typ; cin >> typ;
            if (typ == 1) {
                int x; cin >> x;
                // cout << "Fold: " << x << endl;
                if (!reversed) {
                    if (x <= (to - from) / 2) {
                        REP(t,x) {
                            int val = get(from+x-t) - get(from+x-t-1);
                            update(from+x+t+1, val);
                            update(from+x-t, -val);
                        }
                        from += x;
                    }
                    else {
                        REP(t,(to-from)-x) {
                            int val = get(from+x+t+1) - get(from+x+t);
                            update(from+x-t, val);
                            update(from+x+t+1, -val);
                        }
                        to -= (to-from)-x;
                        reversed = true;
                    }
                }
                else {
                    if (x <= (to - from) / 2) {
                        REP(t,x) {
                            int val = get(to-x+t+1) - get(to-x+t);
                            update(to-x-t, val);
                            update(to-x+t+1, -val);
                        }
                        to -= x;
                    }
                    else {
                        REP(t,(to-from)-x) {
                            int val = get(to-x-t) - get(to-x-t-1);
                            update(to-x+t+1, val);
                            update(to-x-t, -val);
                        }
                        from += (to-from)-x;
                        reversed = false;
                    }
                }
                if (!reversed) {
                    // cout << "Currently: " << from << ' ' << to << endl;
                    // FOR(i,from+1,to) cout << get(i) - get(i-1) << ' '; cout << endl;
                }
                else {
                    // cout << "Currently: " << to << ' ' << from << " (reversed) " << endl;
                    // FORD(i,to,from+1) cout << get(i) - get(i-1) << ' '; cout << endl;
                }
            } else {
                int u, v; cin >> u >> v;
                if (!reversed) {
                    cout << get(from+v) - get(from+u) << "\n";
                }
                else {
                    cout << get(to-u) - get(to-v) << "\n";
                }
            }
        }
        cout << endl;
    }
    return 0;
}

