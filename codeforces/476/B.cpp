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

int c[111][111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(9);
    string s, t;

    FOR(i,0,100) {
        c[i][0] = 1;
        FOR(j,1,i) c[i][j] = c[i-1][j-1] + c[i-1][j];
    }
    while (cin >> s >> t) {
        int pos = 0;
        REP(i,s.length())
            if (s[i] == '+') ++pos;
            else --pos;

        int cnt = 0;
        REP(i,t.length())
            if (t[i] == '+') --pos;
            else if (t[i] == '-') ++pos;
            else ++cnt;

        cout << c[cnt][(cnt + abs(pos)) / 2] * 1.0 / (1<<cnt) << endl;
    }
    return 0;
}

