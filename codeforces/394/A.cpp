#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    string s;
    while (cin >> s) {
        REP(i,s.length()) if (s[i] != '|') s[i] = ' ';
        istringstream ss(s);

        string a, b, c;
        ss >> a >> b >> c;

        int x = a.length(), y = b.length(), z = c.length();

        if (x + y == z) {
            cout << a << '+' << b << '=' << c << endl;
        }
        else if (x + y + 1 == z-1 && z) {
            cout << a << "|+" << b << '=' << c.substr(0, c.length()-1) << endl;
        }
        else if (x + y - 2 == z && x > 1) {
            cout << a.substr(0, a.length()-1) << '+' << b << '=' << c << '|' << endl;
        }
        else if (x + y - 2 == z && y > 1) {
            cout << a << '+' << b.substr(0, b.length()-1) << '=' << c << '|' << endl;
        }
        else cout << "Impossible" << endl;
    }
    return 0;
}
