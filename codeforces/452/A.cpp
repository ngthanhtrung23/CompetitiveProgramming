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

const string can[8] = {"vaporeon", "jolteon", "flareon", "espeon", "umbreon", "leafeon", "glaceon", "sylveon"};

string s;
int n;

bool match(string a, string b) {
    if (a.length() != b.length()) return false;
    REP(x,a.length()) {
        if (b[x] == '.' || a[x] == '.') continue;
        if (b[x] != a[x] && b[x] != (a[x] ^ ' ')) return false;
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        cin >> s;
        REP(x,8) if (match(s, can[x])) {
            cout << can[x] << endl;
            break;
        }
    }
    return 0;
}
