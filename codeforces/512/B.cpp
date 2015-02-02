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

const int MN = 311;
map<int,int> f[MN];

int l[MN], c[MN], n;

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    while (cin >> n) {
        FOR(i,1,n) cin >> l[i];
        FOR(i,1,n) cin >> c[i];

        FOR(i,0,n) f[i].clear();
        f[0][0] = 0;

        FOR(i,0,n-1) {
            for(auto cur : f[i]) {
                int g = cur.first;
                if (f[i+1].count(g)) f[i+1][g] = min(f[i+1][g], f[i][g]);
                else f[i+1][g] = f[i][g];

                int new_g = __gcd(g, l[i+1]);
                if (f[i+1].count(new_g)) f[i+1][new_g] = min(f[i+1][new_g], f[i][g] + c[i+1]);
                else f[i+1][new_g] = f[i][g] + c[i+1];
            }
        }
        if (f[n].count(1)) cout << f[n][1] << endl;
        else cout << -1 << endl;
    }
    return 0;
}
