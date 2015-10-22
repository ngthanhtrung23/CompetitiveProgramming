
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

int main() {
    ios :: sync_with_stdio(false);
    int n;
    string s;
    while (cin >> n >> s) {
        int good = 0, bad = 0;
        REP(i,s.length()) {
            if (s[i] == ':') {
                if (s[i+1] == ')') ++good;
                else if (s[i+1] == '(') ++bad;
            }
            if (s[i+1] == ':') {
                if (s[i] == '(') ++good;
                else if (s[i] == ')') ++bad;
            }
        }
        if (good > bad) puts("HAPPY");
        else if (good < bad) puts("SAD");
        else puts("BORED");
    }
}
