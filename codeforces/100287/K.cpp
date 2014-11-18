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

bool check(string a, string b, int la) {
    for(int x = la, y = 0; x < a.length() && y < b.length(); ++x, ++y)
        if (a[x] == '2' && b[y] == '2') return false;
    return true;
}

int main() {
    freopen("kickdown.in", "r", stdin); freopen("kickdown.out", "w", stdout);
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    string a, b;
    while (cin >> a >> b) {
        int la = a.length(), lb = b.length();
        int res = la + lb;
        for(int start = 0; start <= la; ++start) {
            if (check(a, b, start)) {
                res = min(res, max(la, lb + start));
            }
        }
        for(int start = 0; start <= lb; ++start) {
            if (check(b, a, start)) {
                res = min(res, max(lb, la + start));
            }
        }
        cout << res << endl;
    }
    return 0;
}
