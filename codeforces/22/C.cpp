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

int n, m, v, x;
int ids[100111], nId;
vector< pair<int,int> > res;

#define add(a, b) { res.push_back(make_pair(a, b)); if (res.size() == m) { return true; } }

bool solve() {
    add(x, v);
    FOR(i,1,nId) add(ids[i], v);
    FOR(i,1,nId) FOR(j,i+1,nId) add(ids[i], ids[j]);
    return false;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m >> v) {
        x = 1; if (v == x) ++x;
        FOR(i,1,n) if (i != v && i != x) ids[++nId] = i;
        
        if (m < n-1) {
            cout << -1 << endl;
            continue;
        }

        if (solve()) {
            REP(i,m) cout << res[i].first << ' ' << res[i].second << endl;
        }
        else cout << -1 << endl;
    }
    return 0;
}

