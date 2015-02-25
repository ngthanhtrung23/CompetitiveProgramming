
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

string s, a[11];

int main() {
    while (cin >> s) {
        FOR(i,0,9) cin >> a[i];

        for(int i = 0; i < s.length(); i += 10) {
            string cur = s.substr(i, 10);
            FOR(j,0,9) if (cur == a[j]) {
                cout << j;
                break;
            }
        }
        cout << endl;
    }
    return 0;
}
