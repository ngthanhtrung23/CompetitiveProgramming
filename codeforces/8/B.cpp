
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

string s;
pair<int,int> a[111];

int main() {
    while (cin >> s) {
        int l = s.length();
        a[0] = make_pair(0, 0);
        FOR(i,1,l) {
            char c = s[i-1];
            int u = a[i-1].first, v = a[i-1].second;

            int uu = u, vv = v;
            if (c == 'U') ++uu;
            else if (c == 'D') --uu;
            else if (c == 'L') --vv;
            else ++vv;
            a[i] = make_pair(uu, vv);
        }
        bool ok = true;
        FOR(i,0,l-1) FOR(j,i+1,l) if (a[i] == a[j]) ok = false;
        FOR(i,0,l-2) FOR(j,i+2,l) {
            int d = abs(a[i].first - a[j].first) + abs(a[i].second - a[j].second);
            if (d == 1) {
                ok = false;
                break;
            }
        }
        if (ok) cout << "OK"; else cout << "BUG";
        cout << endl;
    }
    return 0;
}
