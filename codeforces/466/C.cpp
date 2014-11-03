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

const int MN = 500111;
long long a[MN], s[MN], cnt[MN];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    int n;
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) s[i] = s[i-1] + a[i];

        if (s[n] % 3) {
            cout << 0 << endl;
            continue;
        }

        long long each = s[n] / 3;
        FOR(i,1,n) {
            cnt[i] = cnt[i-1];
            if (s[i] == each) ++cnt[i];
        }

        long long res = 0;
        FORD(i,n,2) if (s[n] - s[i-1] == each) {
            res += cnt[i-2];
        }
        cout << res << endl;
    }
    return 0;
}
