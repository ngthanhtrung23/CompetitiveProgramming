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

int n, m, a[111];
bool b[111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m) {
        memset(b, false, sizeof b);
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,m) { int u; cin >> u; b[u] = true; }
        long long res = 0;
        FOR(i,1,n) if (!b[i]) res += a[i];
        vector<long long> cur;
        FOR(i,1,n) if (b[i]) cur.push_back(a[i]);

        sort(cur.begin(), cur.end());

        long long best = 0;
        REP(i,cur.size()+1) {
            long long x = res;
            FOR(j,i,cur.size()-1) x += cur[j];
            FOR(j,0,i-1) x = x * 2;
            best = max(best, x);
        }
        cout << best << endl;
    }
    return 0;
}

