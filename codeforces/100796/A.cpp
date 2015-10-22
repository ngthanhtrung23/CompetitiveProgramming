
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

string a, b, res;

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> a >> b) {
        int la = a.length(), lb = b.length();
        res = "";
        REP(turn,max(la, lb)) res += '0';

        REP(i,max(la,lb)) {
            res[i] = '0' + abs(a[i] - b[i]);
        }

        while (res.length() > 1 && res[0] == '0') res = res.substr(1);
        cout << res << endl;
    }
}
