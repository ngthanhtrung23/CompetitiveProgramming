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

bool canSort(string s, string t) {
    string a = s, b = t;
    sort(a.begin(), a.end());
    sort(b.begin(), b.end());
    return a == b;
}

bool canDel(string s, string t) {
    int i = 0;
    REP(j,t.length()) {
        while (i < s.length() && s[i] != t[j]) ++i;
        if (i == s.length()) return false;
        ++i;
    }
    return true;
}

int cnt[300];

bool canBoth(string s, string t) {
    memset(cnt, 0, sizeof cnt);
    REP(i,s.length()) ++cnt[s[i]];
    REP(i,t.length()) --cnt[t[i]];

    FOR(c,'a','z') if (cnt[c] < 0) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    string s, t;
    while (cin >> s >> t) {
        if (canSort(s, t)) cout << "array" << endl;
        else if (canDel(s, t)) cout << "automaton" << endl;
        else if (canBoth(s, t)) cout << "both" << endl;
        else cout << "need tree" << endl;
    }
    return 0;
}
