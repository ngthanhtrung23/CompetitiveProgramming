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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

const int MN = 50111;
const int oo = 1000111000;
struct Cow {
    int w, s;
    int can;
} a[MN];
int n;

bool operator < (const Cow &a, const Cow &b) {
    return a.s + a.w > b.s + b.w;
}

bool check(int x) {
    int allw = 0;
    FOR(i,1,n) allw += a[i].w;

    int i = 0;
    multiset<int> setw;

    REP(turn,n) {
        while (i < n && a[i+1].w + a[i+1].s >= allw - x) {
            ++i;
            setw.insert(-a[i].w);
        }
        if (setw.empty()) return false;
        int t = *setw.begin();
        allw += t;

        setw.erase(setw.begin());
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i].w >> a[i].s;
        sort(a+1, a+n+1);

        // FOR(i,1,n) cout << a[i].w << ' ' << a[i].s << endl;

        int l = -oo, r = oo, res = oo;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid)) {
                res = mid;
                r = mid - 1;
            } else l = mid + 1;
        }

        cout << res << endl;
    }
    return 0;
}
