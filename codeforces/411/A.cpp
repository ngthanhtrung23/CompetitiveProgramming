#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

char tmp[111];

bool has(char low, char high, string s) {
    REP(i,s.length())
        if (s[i] >= low && s[i] <= high) return true;
    return false;
}

bool check(string s) {
    if (s.length() < 5) return false;
    if (!has('a','z',s)) return false;
    if (!has('A','Z',s)) return false;
    if (!has('0','9',s)) return false;
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    while (gets(tmp)) {
        string s(tmp);
        if (!check(s)) cout << "Too weak\n";
        else cout << "Correct\n";
    }
    return 0;
}
