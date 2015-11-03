
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
    int t, x0, y0, x1, y1;
    string s;
    while (cin >> t >> x0 >> y0 >> x1 >> y1) {
        cin >> s;
        if (x0 == x1 && y0 == y1) cout << 0 << endl;
        else {
            try {
                REP(i,SZ(s)) {
                    if (s[i] == 'E' && x0 < x1) ++x0;
                    else if (s[i] == 'S' && y0 > y1) --y0;
                    else if (s[i] == 'W' && x0 > x1) --x0;
                    else if (s[i] == 'N' && y0 < y1) ++y0;

                    if (x0 == x1 && y0 == y1) {
                        cout << i+1 << endl;
                        throw 1;
                    }
                }
                cout << -1 << endl;
            } catch(int e) {
            }
        }
    }
}
