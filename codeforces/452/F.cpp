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

const int MN = 300111;
const int GH = 211;
int n, a[MN], id[MN];

bool solve() {
    FOR(y,1,n) {
        FOR(d,1,GH) {
            int x = y - d, z = y + d;
            if (x < 1 || z > n) break;
            if (id[x] < id[y] && id[y] < id[z]) return true;
            if (id[z] < id[y] && id[y] < id[x]) return true;
        }
    }
    FOR(j,1,n) {
        FOR(i,max(1,j-GH),j-1) {
            int z = a[j] + a[j] - a[i];
            if (0 < z && z <= n && id[z] > j) return true;
        }
        FOR(k,j+1,min(n,j+GH)) {
            int x = a[j] + a[j] - a[k];
            if (0 < x && x <= n && id[x] < j) return true;
        }
    }
    return false;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) id[a[i]] = i;

        cout << (solve() ? "YES" : "NO") << endl;
    }
    return 0;
}
