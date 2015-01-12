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
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    int n;
    while (cin >> n) {
        map<string,string> orig;
        while (n--) {
            string a, b; cin >> a >> b;
            if (orig.find(a) == orig.end()) {
                orig[b] = a;
            }
            else {
                string c = orig[a];
                orig.erase(a);
                orig[b] = c;
            }
        }
        cout << orig.size() << "\n";
        for(auto e : orig)
            cout << e.second << ' ' << e.first << "\n";
    }
    return 0;
}
