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
    int ntest; cin >> ntest;
    while (ntest--) {
        long long l, r; cin >> l >> r;
        long long saver = r;
        if (l == 0 && r == 0) {
            cout << 0 << endl;
            continue;
        }
        if (l == 0) ++l;
        string ls = "", rs = "";
        while (l) {
            ls = (char) (l % 2 + '0') + ls;
            l /= 2;
        }
        while (r) {
            rs = (char) (r % 2 + '0') + rs;
            r /= 2;
        }
        while (ls.length() < rs.length()) ls = "0" + ls;

        // DEBUG(ls);
        // DEBUG(rs);

        long long res = 0;
        REP(i,ls.size()+1) {
            long long cur = 0;
            for(int x = 0; x < i; ++x)
                cur = cur * 2 + ls[x] - '0';
            for(int x = i; x < ls.size(); ++x)
                cur = cur * 2 + 1;
            if (cur <= saver && __builtin_popcountll(cur) > __builtin_popcountll(res))
                res = cur;
        }
        cout << res << endl;
    }
    return 0;
}