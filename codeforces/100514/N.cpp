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

map<int,char> m;

void go(char c, int u) {
    while (u <= 30) {
        m[u] = c;
        c += 2;
        u += 8;
    }
}

string de(string s) {
    string res = "";
    REP(i,s.length()) {
        if (m.count(s[i])) res += m[s[i]];
        else res += '?';
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    go('a', 0);
    go('b', 1);
    go('i', 4);
    go('j', 5);
    go('q', 2);
    go('r', 3);
    go('y', 6);
    go('z', 7);

    int n;
    while (cin >> n) {
        FOR(i,1,n) {
            int u; cin >> u;
            if (m.count(u)) cout << m[u];
            else cout << '?';
        }
        cout << endl;
    }
    return 0;
}
