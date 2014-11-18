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

int main() {
    freopen("graveyard.in", "r", stdin); freopen("graveyard.out", "w", stdout);
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int has, add;
    while (cin >> has >> add) {
        vector<double> a, b;
        double each = 10000 / (double) has;
        double cur = 0;
        REP(i,has) {
            a.push_back(cur);
            cur += each;
        }

        each = 10000 / (double) (has + add);
        cur = 0;
        REP(i,has+add) {
            b.push_back(cur);
            cur += each;
        }

        // PR0(a, a.size());
        // PR0(b, b.size());
        set<double> s(b.begin(), b.end());

        double res = 0;
        REP(i,has) {
            auto it = s.lower_bound(a[i]);
            if (it == s.end()) --it;
            if (it != s.begin()) {
                auto it2 = it; --it2;
                if (fabs(*it - a[i]) > fabs(*it2 - a[i])) {
                    it = it2;
                }
            }
            res += fabs(*it - a[i]);
            s.erase(it);
        }
        cout << res << endl;
    }
    return 0;
}
