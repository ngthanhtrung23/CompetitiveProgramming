
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

const int MN = 511;
int m, n, d, a[MN][MN];
int lab[MN*MN], maxH[MN*MN];

pair< int, pair<int,int> > all[MN * MN];

int getId(int i, int j) {
    return (i-1) * n + j;
}

int getRoot(int u) {
    if (lab[u] < 0) return u;
    return lab[u] = getRoot(lab[u]);
}

void merge(int u, int v) {
    lab[v] += lab[u];
    lab[u] = v;
    maxH[v] = max(maxH[v], maxH[u]);
}

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

void expand(int u, int v) {
    REP(dir,4) {
        int uu = u + di[dir], vv = v + dj[dir];
        if (uu < 1 || uu > m || vv < 1 || vv > n) continue;
        if (a[uu][vv] < a[u][v]) continue;

        int x = getId(u, v), y = getId(uu, vv);
        x = getRoot(x); y = getRoot(y);

        if (x != y) merge(x, y);
    }
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> m >> n >> d;
        int k = 0;
        FOR(i,1,m) FOR(j,1,n) {
            cin >> a[i][j];
            all[++k] = make_pair(a[i][j], make_pair(i, j));
        }
        sort(all+1, all+k+1);
        FOR(i,1,m) FOR(j,1,n) {
            lab[ getId(i, j) ] = -1;
            maxH[ getId(i, j)] = a[i][j];
        }

        int j = m*n + 1, res = 0;
        FORD(i,m*n,1) {
            while (j > 1 && all[j-1].first > all[i].first - d) {
                --j;
                expand(all[j].second.first, all[j].second.second);
            }
            int u = getRoot(getId(all[i].second.first, all[i].second.second));

            if (maxH[u] == all[i].first) {
                ++res;
            }
        }
        cout << res << '\n';
    }
}

