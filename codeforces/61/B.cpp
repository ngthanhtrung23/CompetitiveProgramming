
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

string a, b, c;

string refine(string s) {
    string res;
    for(char c : s) {
        if (c >= 'a' && c <= 'z') res += c;
        else if (c >= 'A' && c <= 'Z') res += (char) (c ^ ' ');
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> a >> b >> c) {
        a = refine(a);
        b = refine(b);
        c = refine(c);

        int q; cin >> q;
        while (q--) {
            string s; cin >> s; s = refine(s);
            if (s == a + b + c
                    || s == a + c + b
                    || s == b + a + c
                    || s == b + c + a
                    || s == c + a + b
                    || s == c + b + a)
                cout << "ACC";
            else cout << "WA";
            cout << '\n';
        }
    }
    return 0;
}
