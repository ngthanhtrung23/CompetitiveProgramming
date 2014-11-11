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

int n, pos;
string s;

bool check() {
    REP(i,s.length())
        if (s[i] != s[s.length()-i-1]) return false;
    return true;
}

int dist(char a, char b) {
    if (a > b) swap(a, b);
    return min(b - a, 'z' - b + 1 + a - 'a');
}

int left() {
    int res = 0;
    for(int i = pos; i >= 0; --i)
        res += 1 + dist(s[i], s[s.length()-i-1]);
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> pos) {
        cin >> s;
        if (check()) {
            cout << 0 << endl;
            continue;
        }

        int res = 0, l = -1, r = -1;
        REP(i,s.length()) if (i <= s.length()-i-1) {
            char x = s[i], y = s[s.length()-i-1];
            if (x != y) {
                if (l < 0) l = i;
                r = i;
                res += dist(x, y);
            }
        }
        --pos;
        int go = 1000111000;
        go = min(go, abs(pos - l) + r - l);
        go = min(go, abs(pos - r) + r - l);
        l = s.length()-l-1;
        r = s.length()-r-1;
        swap(l, r);
        go = min(go, abs(pos - l) + r - l);
        go = min(go, abs(pos - r) + r - l);
        cout << res + go << endl;
    }
    return 0;
}

