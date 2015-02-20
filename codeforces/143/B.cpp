
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
        bool neg = false;
        if (s[0] == '-') {
            neg = true;
            s = s.substr(1);
        }

        string x = "", y = "";
        if (s.find('.') == string::npos) {
            x = s;
            y = "00";
        }
        else {
            int t = s.find('.');
            x = s.substr(0, t);
            y = s.substr(t + 1);
        }

        string xx = "";
        while (x.length() % 3) x = '0' + x;
        for(int i = 0; i < x.length(); i += 3) {
            xx += x[i];
            xx += x[i+1];
            xx += x[i+2];
            xx += ',';
        }
        xx = xx.substr(0, xx.length()-1);
        while (xx.size() > 1 && xx[0] == '0') xx = xx.substr(1);

        while (y.length() < 2) y += '0';
        if (y.length() > 2) y = y.substr(0, 2);

        if (neg) cout << '(';
        cout << '$';
        cout << xx << '.' << y;
        if (neg) cout << ')';
        cout << endl;
    }
    return 0;
}
