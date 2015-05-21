
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 100111;
string s[MN];
int n;

int go(int start, bool trace) {
    if (start > n) return 0;

    if (s[start] == "int") {
        if (trace) cout << "int";
        return start + 1;
    }
    else {
        if (trace) cout << "pair<";
        int part2 = go(start+1, trace);
        if (!part2) return 0;

        if (trace) cout << ',';
        int res = go(part2, trace);
        if (!res) return 0;
        if (trace) cout << '>';

        return res;
    }
}

char tmp[1000111];

int main() {
    int need;
    while (scanf("%d\n", &need) == 1) {
        gets(tmp);
        istringstream ss(tmp);
        n = 0;
        while (ss >> s[n+1]) ++n;

        if (go(1, false) == n+1) {
            go(1, true);
            cout << endl;
        }
        else cout << "Error occurred" << endl;
    }
    return 0;
}
