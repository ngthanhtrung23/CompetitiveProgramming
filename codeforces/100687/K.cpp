
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

char a[111][111];

int main() {
    ios :: sync_with_stdio(false);
    int startu, startv, targetu, targetv;
    FOR(i,1,16) FOR(j,1,32) {
        cin >> a[i][j];
        if (a[i][j] == ':') {
            startu = i;
            startv = j;
        }
        else if (a[i][j] == 'E') {
            targetu = i;
            targetv = j;
        }
    }
    string s; cin >> s;
    for(char c : s) {
        if (c == 'v') ++startu;
        else if (c == '^') --startu;
        else if (c == '<') --startv;
        else if (c == '>') ++startv;
    }
    cout << ((startu == targetu && startv == targetv) ? "Yes" : "No") << endl;
    return 0;
}
