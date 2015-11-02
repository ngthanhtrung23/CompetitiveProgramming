
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

const int MN = 111;

int n, m;
pair<int,int> a[MN];
int side[MN];
int ke[MN][MN];

void dfs(int u, int col) {
    side[u] = col;
    FOR(v,1,m) if (ke[u][v]) {
        if (side[v] < 0) {
            dfs(v, 1 - col);
        }
        else {
            if (side[v] == side[u]) throw 1;
        }
    }
}

bool inside(int l, int r, int u) {
    if (l <= r) return l <= u && u <= r;
    return l <= u || u <= r;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,m) {
            cin >> a[i].first >> a[i].second;
        }
        memset(ke, 0, sizeof ke);
        FOR(i,1,m) FOR(j,i+1,m) {
            int l = a[i].first, r = a[i].second;
            int u = a[j].first, v = a[j].second;

            if (l == u || l == v) continue;
            if (r == u || r == v) continue;

            if ((inside(l, r, u) ^ inside(l, r, v))
                    || inside(u, v, l) ^ inside(u, v, r)) {
                ke[i][j] = ke[j][i] = 1;
            }
        }
        memset(side, -1, sizeof side);
        try {
            FOR(i,1,m) if (side[i] < 0) {
                dfs(i, 0);
            }
            FOR(i,1,m) {
                cout << (side[i] == 0 ? 'o' : 'i');
            }
            cout << endl;
        } catch (int e) {
            cout << "Impossible" << endl;
        }
    }
}

