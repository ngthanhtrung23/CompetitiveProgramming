
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

const int MN = 1211;

int n;
double x[MN], y[MN], c[MN][MN], val;
int color[MN];

void dfs(int u) {
    FOR(v,1,n) if (v != u && c[u][v] < val) {
        if (color[v] == color[u]) throw 1;

        if (!color[v]) {
            color[v] = 3 - color[u];
            dfs(v);
        }
    }
}

bool check(double val) {
    ::val = val;
    memset(color, 0, sizeof color);
    
    FOR(i,1,n) if (!color[i]) {
        color[i] = 1;
        try {
            dfs(i);
        } catch (...) {
            return false;
        }
    }
    return true;
}

int main() {
    ios :: sync_with_stdio(false);
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);

    cout << (fixed) << setprecision(12);

    while (cin >> n) {
        FOR(i,1,n) cin >> x[i] >> y[i];
        FOR(i,1,n) FOR(j,1,n) c[i][j] = sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));

        double l = 0, r = 4e4;
        REP(turn,80) {
            double mid = (l + r) / 2.0;
            if (check(mid)) l = mid;
            else r = mid;
        }
        cout << l / 2.0 << endl;
        check(l);

        FOR(i,1,n) cout << color[i] << ' '; cout << endl;
    }
}

