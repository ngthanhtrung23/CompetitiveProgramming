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

const int MN = 100111;
int n;
long long a[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        long long sumAll = 0;
        FOR(i,1,n) {
            cin >> a[i];
            sumAll += a[i];
        }

        long long res = 0;
        int first = n/2;
        multiset<long long> s;
        FOR(i,1,first) {
            int x = a[i*2-1], y = a[2 * i];

            s.insert(x);
            s.insert(y);

            res += *s.begin();
            s.erase(s.begin());
        }

        cout << sumAll - res << ' ' << res << endl;
    }
    return 0;
}

