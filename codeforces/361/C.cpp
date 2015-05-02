
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

const int MN = 5011;
int n, m;
long long initial[MN], add[MN], a[MN];
tuple<int,int,int,int> op[MN];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) initial[i] = 1000 * 1000 * 1000, add[i] = 0;

        FOR(i,1,m) {
            int typ, u, v, val; cin >> typ >> u >> v >> val;
            if (typ == 1) {
                FOR(i,u,v) add[i] += val;
            }
            else {
                FOR(i,u,v) initial[i] = min(initial[i], val - add[i]);
            }
            op[i] = make_tuple(typ, u, v, val);
        }

        FOR(i,1,n) a[i] = initial[i];
        bool ok = *min_element(a+1, a+n+1) >= -1000 * 1000 * 1000
            && *max_element(a+1, a+n+1) <= 1000 * 1000 * 1000;
        FOR(i,1,m) {
            int typ = get<0>(op[i]),
                u = get<1>(op[i]),
                v = get<2>(op[i]),
                val = get<3>(op[i]);

            if (typ == 1) {
                FOR(x,u,v) a[x] += val;
            }
            else {
                int ln = -1000111000;
                FOR(x,u,v) if (ln < a[x]) ln = a[x];
                if (ln != val) ok = false;
            }
        }
        if (!ok) cout << "NO" << endl;
        else {
            cout << "YES" << endl;
            FOR(i,1,n) cout << initial[i] << ' '; cout << endl;
        }
    }
    return 0;
}
