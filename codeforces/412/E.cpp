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

long long f[1000111][6];
string s;

bool lower(char c) { return c >= 'a' && c <= 'z'; }
bool digit(char c) { return c >= '0' && c <= '9'; }

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s) {
        int n = s.length();
        s = " " + s;
        memset(f, 0, sizeof f);

        long long res = 0;
        FOR(i,1,n) {
            // First part
            if (lower(s[i]) || digit(s[i]) || s[i] == '_') f[i][1] = f[i-1][1];
            if (lower(s[i])) f[i][1] += 1;

            // @
            if (s[i] == '@') f[i][2] = f[i-1][1];

            // 3rd part
            if (lower(s[i]) || digit(s[i])) f[i][3] = f[i-1][2] + f[i-1][3];

            // .
            if (s[i] == '.') f[i][4] = f[i-1][3];

            // 5th part
            if (lower(s[i])) f[i][5] = f[i-1][4] + f[i-1][5];

            res += f[i][5];
        }
        cout << res << endl;
    }
    return 0;
}
