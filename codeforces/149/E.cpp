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

#define left left_
#define right right_
#define next next_

const int MN = 100111;
string s;
int left[MN], right[MN];
string t;
int next[2][1011];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> s) {
        int ls = s.length();
        int q; cin >> q;
        int res = 0;
        while (q--) {
            cin >> t; int lt = t.length();
            if (lt == 1) continue;
            REP(turn,2) {
                next[turn][0] = -1;
                int j = -1;
                FOR(i,1,lt-1) {
                    while (j >= 0 && t[i] != t[j+1]) j = next[turn][j];
                    if (t[i] == t[j+1]) ++j;
                    next[turn][i] = j;
                }
                reverse(t.begin(), t.end());
            }

            int j = -1;
            FOR(i,0,s.length()) {
                while (j >= 0 && s[i] != t[j+1]) j = next[0][j];
                if (s[i] == t[j+1]) ++j;
                left[i] = j + 1;
                if (j == lt-1) j = next[0][j];
            }
            reverse(t.begin(), t.end());

            j = -1;
            FORD(i,s.length()-1,0) {
                while (j >= 0 && s[i] != t[j+1]) j = next[1][j];
                if (s[i] == t[j+1]) ++j;
                right[i] = j + 1;
                if (j == lt-1) j = next[1][j];
            }

            FOR(i,1,s.length()-1) left[i] = max(left[i], left[i-1]);
            FORD(i,s.length()-2,0) right[i] = max(right[i], right[i+1]);


            FOR(i,0,s.length()-1) {
                if (left[i] + right[i+1] >= lt) {
                    ++res;
                    break;
                }
            }
        }
        cout << res << endl;
    }
    return 0;
}
