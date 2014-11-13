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

int n;
pair<int,int> a[1011];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i].second >> a[i].first;
            if (a[i].second > a[i].first) swap(a[i].second, a[i].first);
        }

        // Sort by end points
        sort(a+1, a+n+1);

        int last = -10111;
        vector< int > res;
        FOR(i,1,n) {
            // If last >= start point --> can ignore
            if (last >= a[i].second) continue;

            res.push_back(a[i].first);
            last = a[i].first;
        }
        cout << res.size() << endl;
        REP(i,res.size()) cout << res[i] << ' '; cout << endl;
    }
    return 0;
}

