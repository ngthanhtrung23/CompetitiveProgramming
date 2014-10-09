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
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

string get(string s) {
    if (s[s.length()-1] == 'x' || s[s.length()-1] == 's' || s[s.length()-1] == 'o') return s + "es";
    if (s[s.length()-1] == 'h' && s[s.length()-2] == 'c') return s + "es";

    if (s[s.length()-1] == 'y') return s.substr(0, s.length()-1) + "ies";

    if (s[s.length()-1] == 'f') return s.substr(0, s.length()-1) + "ves";
    if (s[s.length()-1] == 'e' && s[s.length()-2] == 'f') return s.substr(0, s.length()-2) + "ves";

    return s + "s";
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    freopen("input.txt", "r", stdin); freopen("output.txt", "w", stdout);
    int ntest; cin >> ntest;
    while (ntest--) {
        string s; cin >> s;
        cout << get(s) << "\n";
    }
    return 0;
}
