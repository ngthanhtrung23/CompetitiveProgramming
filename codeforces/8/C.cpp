
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define TWO(X) (1<<(X))
#define CONTAIN(S,X) (S & TWO(X))
using namespace std;

const int oo = 1000111000;

pair<int,int> a[111], start;
int n, d[111][111];
int f[TWO(24)], tr[TWO(24)];

void update(int x, int val, int cur) {
    if (f[x] > val) {
        f[x] = val;
        tr[x] = cur;
    }
}

void trace(int mask) {
    if (mask == 0) return ;
    trace(tr[mask]);

    REP(u,n)
        if (CONTAIN(mask,u) && !CONTAIN(tr[mask], u))
            cout << 1+u << ' ';
    cout << 0 << ' ';
}

int main() {
    while (cin >> start.first >> start.second) {
        cin >> n;
        REP(i,n) cin >> a[i].first >> a[i].second;
        a[n] = start;

        REP(i,n+1) REP(j,n+1)
            d[i][j] = sqr(a[i].first - a[j].first) + sqr(a[i].second - a[j].second);
        REP(i,TWO(n)) f[i] = oo;
        f[0] = 0;
        REP(mask,TWO(n)-1) if (f[mask] < oo) {
            int u = 0;
            while (CONTAIN(mask,u)) ++u;

            update(mask + TWO(u), f[mask] + d[n][u] + d[u][n], mask);
            FOR(v,u+1,n-1)
                if (!CONTAIN(mask,v))
                    update(mask + TWO(u) + TWO(v), f[mask] + d[n][u] + d[u][v] + d[v][n], mask);
        }
        cout << f[TWO(n)-1] << endl;
        cout << 0 << ' ';
        trace(TWO(n)-1);
        cout << endl;
    }
    return 0;
}
