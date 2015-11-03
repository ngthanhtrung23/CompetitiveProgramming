
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

int n, q;
ll a[100111];

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d%d", &n, &q) == 2) {
        FOR(i,1,n) {
            int x; scanf("%d", &x);
            a[i] = x;
        }
        ll addAll = 0;
        while (q--) {
            int typ; scanf("%d", &typ);
            if (typ == 1) {
                int v, x; scanf("%d%d", &v, &x);
                a[v] = x - addAll;
            }
            else if (typ == 2) {
                int y; scanf("%d", &y);
                addAll += y;
            }
            else if (typ == 3) {
                int v; scanf("%d", &v);
                printf("%d\n", (int) (a[v] + addAll));
            }
        }
    }
}
