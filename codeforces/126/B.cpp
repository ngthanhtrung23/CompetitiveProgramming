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

#define next next_
int next[1000111];

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    string s;
    while (cin >> s) {
        next[0] = -1;
        int j = -1;
        FOR(i,1,s.length()-1) {
            while (j >= 0 && s[i] != s[j+1]) j = next[j];
            if (s[i] == s[j+1]) ++j;
            next[i] = j;
        }
        if (next[s.length()-1] < 0) {
            cout << "Just a legend" << endl;
            continue;
        }

        bool ok = false;
        REP(i,s.length()-1) if (next[i] == next[s.length()-1]) {
            cout << s.substr(0, next[i]+1) << endl;
            ok = true;
            break;
        }
        if (!ok) {
            if (next[next[s.length()-1]] == -1) {
                cout << "Just a legend" << endl;
            } else {
                cout << s.substr(0, 1 + next[next[s.length()-1]]) << endl;
            }
        }
    }
    return 0;
}

