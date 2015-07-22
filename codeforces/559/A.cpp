
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
using namespace std;

int main() {
    ios :: sync_with_stdio(false);
    ll a1, a2, a3, a4, a5, a6;
    while (cin >> a1 >> a2 >> a3 >> a4 >> a5 >> a6) {
        cout << 2 * (a1*a2 + a3*a4 + a5*a6) + (a2 - a5) * (a2 - a5) << endl;
    }
}
