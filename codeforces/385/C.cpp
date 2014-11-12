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

const int MN = 1000111;
const int MV = 10000000;
int sieve[MV+11], cnt[MV+11];
int n;

void init() {
    for(int i = 2; i*i <= MV; ++i)
        if (!sieve[i]) {
            for(int j = i*i; j <= MV; j += i) {
                sieve[j] = i;
            }
        }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    init();
    while (cin >> n) {
        memset(cnt, 0, sizeof cnt);
        FOR(i,1,n) {
            int a; cin >> a;
            while (sieve[a]) {
                int p = sieve[a];
                ++cnt[p];
                while (a % p == 0) a /= p;
            }
            if (a > 1) {
                ++cnt[a];
            }
        }
        FOR(i,1,MV) cnt[i] += cnt[i-1];
        // PR(cnt, 15);

        int q; cin >> q;
        while (q--) {
            int l, r; cin >> l >> r;
            if (l > MV) cout << 0 << "\n";
            else {
                if (r > MV) r = MV;
                cout << cnt[r] - cnt[l-1] << "\n";
            }
        }
    }
    return 0;
}
