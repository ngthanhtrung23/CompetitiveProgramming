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

int n, p[55], price[5];
ll has[5];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> p[i];
        REP(i,5) cin >> price[i];

        memset(has, 0, sizeof has);
        ll cur = 0;
        FOR(i,1,n) {
            cur += p[i];
            FORD(i,4,0) {
                ll add = cur / price[i];
                cur -= price[i] * add;
                has[i] += add;
            }
        }
        REP(i,5) cout << has[i] << ' '; cout << endl << cur << endl;
    }
}
