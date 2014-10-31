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

const int MN = 1000111;

int d[MN], x[MN];
multiset<int> s;
int n, k;

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> k) {
        FOR(i,1,n) cin >> d[i];
        sort(d+1, d+n+1);

        FOR(i,1,k) cin >> x[i];
        multiset<int> s;
        FOR(i,1,k) s.insert(x[i]);

        bool ok = true;
        FORD(i,n,1) {
            auto it = s.lower_bound(5*d[i]);
            if (it != s.end()) {
                s.erase(it);
                continue;
            }

            it = s.lower_bound(3*d[i]);
            if (it == s.end()) {
                ok = false;
                break;
            }
            s.erase(it);

            it = s.lower_bound(2*d[i]);
            if (it == s.end()) {
                ok = false;
                break;
            }
            s.erase(it);
        }
        if (!ok) cout << "NIE" << endl;
        else cout << k - s.size() << endl;
    }
    return 0;
}
