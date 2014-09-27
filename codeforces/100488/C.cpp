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

int main() {
    ios :: sync_with_stdio(false);
    long long k;
    while (cin >> k) {
        vector<long long> uoc;
        for(int i = 1; i * i <= k; ++i)
            if (k % i == 0) {
                uoc.push_back(i);
                if (i * i != k) uoc.push_back(k/i);
            }

        set<long long> all;
        REP(i,uoc.size()) REP(j,uoc.size())
            all.insert(uoc[i] * uoc[j]);

        cout << all.size() << endl;
        for(__typeof(all.begin()) it = all.begin(); it != all.end(); ++it) {
            cout << (*it + k) << ' ' << (k + k*k / *it) << endl;
        }
    }
    return 0;
}
