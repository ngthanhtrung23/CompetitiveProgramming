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

const int M = 100111;
int x[M], p[M], m[M];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int test; cin >> test;
    while (test--) {
        int n; cin >> n;
        FOR(i,1,n) cin >> x[i] >> p[i] >> m[i];

        multiset< pair<int,int> > all;
        long long res = 0;
        FORD(i,n,1) {
            all.insert(make_pair(-p[i], m[i]));

            while (x[i] && !all.empty()) {
                int price = -all.begin()->first;
                int amount = all.begin()->second;
                all.erase(all.begin());

                int can = min(amount, x[i]);

                res += can * (long long) price;
                x[i] -= can;
                amount -= can;
                if (amount > 0) all.insert(make_pair(-price, amount));
            }
        }
        cout << res << endl;
    }
    return 0;
}
