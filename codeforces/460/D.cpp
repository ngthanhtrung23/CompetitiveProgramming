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

#define FOR(i,a,b) for(__typeof(a) i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(__typeof(a) i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define ll long long
ll l, r, k, resSum;
vector< ll > res;

void update(vector<ll> x) {
    if (x.size() > k) return ;
    ll sum = 0;
    REP(i,x.size()) sum ^= x[i];
    if (sum < resSum) {
        resSum = sum;
        res = x;
    }
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> l >> r >> k) {
        res.clear();
        resSum = 1000111000111000LL;

        update(vector<ll> {l});
        if (r - l + 1 < 5) {
            FOR(x,l,r) FOR(y,x+1,r)
                update(vector<ll> {x, y});
            FOR(x,l,r) FOR(y,x+1,r) FOR(z,y+1,r)
                update(vector<ll> {x, y, z});
            FOR(x,l,r) FOR(y,x+1,r) FOR(z,y+1,r) FOR(t,z+1,r)
                update(vector<ll> {x, y, z, t});
        }
        else {
            if (l+1 <= r) update(vector<ll> {l, l+1});
            if (l+2 <= r) update(vector<ll> {l+1, l+2});
            if (l+3 <= r) update(vector<ll> {l, l+1, l+2, l+3});
            if (l+4 <= r) update(vector<ll> {l+1, l+2, l+3, l+4});

            ll x = 1, y = 2, z = 3;
            REP(turn,50) {
                if (l <= x && z <= r)
                    update(vector<ll> {x, y, z});

                x = x * 2 + 1;
                y = y * 2 + 1;
                z = z * 2;
            }
        }

        cout << resSum << endl;
        cout << res.size() << endl;
        REP(i,res.size()) cout << res[i] << ' '; cout << endl;
    }
    return 0;
}
