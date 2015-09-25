
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

int n, a[200111];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        REP(i,n) {
            cin >> a[i];
            a[i] += i;
        }
        sort(a, a+n);
        REP(i,n) a[i] -= i;

        try {
            REP(i,n-1) {
                if (a[i] > a[i+1]) throw 1;
            }

            REP(i,n) cout << a[i] << ' '; cout << endl;
        } catch (...) {
            cout << ":(" << endl;
        }
    }
}
