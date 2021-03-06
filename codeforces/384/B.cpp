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

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n, m, k;
    while (cin >> n >> m >> k) {
        int x; FOR(i,1,n) FOR(j,1,m) cin >> x;
        swap(n, m);
        vector< pair<int,int> > res;
        if (k == 0) {
            FOR(i,1,n) FOR(j,i+1,n) res.push_back(make_pair(i, j));
        }
        else {
            FOR(i,1,n) FOR(j,i+1,n) res.push_back(make_pair(j, i));
        }
        cout << res.size() << endl;
        REP(i,res.size()) cout << res[i].first << ' ' << res[i].second << endl;
    }
    return 0;
}
