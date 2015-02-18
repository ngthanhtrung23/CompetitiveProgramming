
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

const int MN = 1000111;

long long p[MN], h[MN], h2[MN];

int n, m;
pair<int,int> e[MN];

int main() {
    ios :: sync_with_stdio(false);
    cout << (fixed) << setprecision(9);
    p[0] = 1;
    FOR(i,1,MN-1) p[i] = p[i-1] * 5;

    while (cin >> n >> m) {
        memset(h, 0, sizeof h);

        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            e[i] = make_pair(u, v);

            h[u] = h[u] + p[v];
            h[v] = h[v] + p[u];
        }

        FOR(i,1,n) h2[i] = h[i];

        sort(h+1, h+n+1);
        ll res = 0;

        int i = 1;
        while (i <= n) {
            int j = i;
            while (j+1 <= n && h[j] == h[j+1]) ++j;

            ll len = j - i + 1;
            res += len * (len-1) / 2;

            i = j + 1;
        }

        FOR(i,1,m) {
            int u = e[i].first, v = e[i].second;
            if (h2[u] + p[u] == h2[v] + p[v]) ++res;
        }
        cout << res << endl;
    }
    return 0;
}

