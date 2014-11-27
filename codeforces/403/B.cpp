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

map<int,int> val;
const int MN = 5011;
int a[MN], n, m;

int get(int x) {
    if (val.count(x)) return val[x];

    int res = 0, savex = x;
    for(int i = 2; i * i <= x; ++i)
        if (x % i == 0) {
            int g;
            if (val.count(i)) g = val[i];
            else g = 1;

            while (x % i == 0) {
                res += g;
                x /= i;
            }

            return val[savex] = res + get(x);
        }
    return 1;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> n >> m) {
        val.clear(); val[1] = 0;
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,m) {
            int b; cin >> b;
            val[b] = -1;
        }

        while (true) {
            int r = -1;
            int g = a[1];
            FOR(i,1,n) {
                g = __gcd(g, a[i]);
                if (get(g) < 0) r = i;
            }
            if (r < 0) break;
            g = a[1];
            FOR(i,1,r) g = __gcd(g, a[i]);
            FOR(i,1,r) a[i] /= g;
        }
        int res = 0;
        FOR(i,1,n) res += get(a[i]);
        cout << res << endl;
    }
    return 0;
}
