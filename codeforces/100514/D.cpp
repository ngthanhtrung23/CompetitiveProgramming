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
    string s;
    while (cin >> s) {
        REP(i,s.length()) if (s[i] == ',') s[i] = ' ';
        stringstream ss(s);

        char c;
        vector<int> bits;
        int cur;
        while (ss >> c) {
            if (c == 'Z') cur = 0;
            if (c == 'O') cur = 1;
            if (c >= '0' && c <= '9') {
                REP(turn,c-'0') bits.push_back(cur);
                cur = 1 - cur;
            }
        }
        for(int i = 0; i < bits.size(); i += 8) {
            int u = 0;
            REP(j,8)
                u = u * 2 + bits[i+j];
            cout << (char) u;
        }
        cout << endl;
    }
    return 0;
}
