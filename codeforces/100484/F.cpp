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

const int MN = 100111;
string s[MN];
int n;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> s[n+1]) ++n;

    int spaces = 0;
    FOR(i,1,n) {
        if (i > 1) {
            int equal = 0;
            while (equal < s[i].length() && equal < s[i-1].length() && s[i][equal] == s[i-1][equal])
                ++equal;

            if (equal > spaces) ++spaces;
            else if (equal < spaces) spaces = equal;
        }
        REP(turn,spaces) putchar(' ');
        puts(s[i].c_str());
    }
    return 0;
}
