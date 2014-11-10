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

#define int long long 
int n, k, d1, d2;

bool solve(int d1, int d2) {
    if (n % 3) return false;
    int each = n / 3;

    if ((k - d1 - d2 - d2) % 3) return false;
    int z = (k - d1 - d2 - d2) / 3;
    int y = z + d2;
    int x = y + d1;

    if (x > k || y > k || z > k) return false;
    return x >= 0 && x <= each && y >= 0 && y <= each && z >= 0 && z <= each;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n >> k >> d1 >> d2;
        if (solve(d1, d2) || solve(d1, -d2) || solve(-d1, d2) || solve(-d1, -d2)) cout << "yes";
        else cout << "no";
        cout << endl;
    }
    return 0;
}
