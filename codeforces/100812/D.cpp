
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

const int MN = 200111;

int n;
ll a[MN];
map<ll, int> id;

int main() {
	ios :: sync_with_stdio(0); cin.tie(0);
	cout << (fixed) << setprecision(9);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) {
            int x; scanf("%d", &x);
            a[i] = x + a[i-1];
        }
        id.clear();
        id[0] = 0;

        int best = MN;
        int l = -1, r = -1;
        FOR(i,1,n) {
            if (id.count(a[i])) {
                int j = id[a[i]];
                if (i - j < best) {
                    best = i - j;
                    l = j + 1;
                    r = i - j;
                }
            }
            id[a[i]] = i;
        }
        if (best == MN) cout << -1 << endl;
        else cout << l << ' ' << r << endl;
    }
}
