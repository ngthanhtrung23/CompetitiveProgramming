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

string s, a[100111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s) {
        int n = s.length();
        FOR(i,1,n) a[i] = "";

        int cnt = 1; a[1] += s[0];
        FOR(i,1,n-1) {
            if (s[i] == '0') a[cnt] += '0';
            else a[++cnt] += s[i];
        }
        // PR(a, cnt);

        int res = cnt;
        int sumlen = 0;
        FOR(i,1,cnt - 1) {
            // a[1] + ... + a[i] < a[i+1]

            sumlen += a[i].length();
            if (sumlen < a[i+1].length() || (sumlen == a[i+1].length() && a[1][0] < a[i+1][0]))
                res = cnt - i;
        }
        cout << res << endl;
    }
    return 0;
}
