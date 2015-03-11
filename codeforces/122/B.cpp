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

int main() {
    string s;
    while (cin >> s) {
        int c4 = 0, c7 = 0;
        for(char c : s) {
            if (c == '4') ++c4;
            else if (c == '7') ++c7;
        }
        if (c4 == 0 && c7 == 0) cout << -1;
        else if (c4 >= c7) cout << '4';
        else cout << '7';
        cout << endl;
    }
    return 0;
}
