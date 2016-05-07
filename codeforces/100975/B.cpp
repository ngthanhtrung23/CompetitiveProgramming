
#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

double safe_sqrt(double x) {
    return sqrt(max(0.0,x));
}
int GI(int& x) {
    return scanf("%lld", &x);
}

int n;
char a[44][44];
pair<int,int> from[44][44], to[44][44], rot[44][44];
int res[44][44];

bool inside(int i, int j) {
    return i > 0 && i <= n && j > 0 && j <= n;
}

pair<int,int> rotate(int i, int j) {
    return make_pair(n+1-j, i);
}

int check() {
    memset(res, 0, sizeof res);
    // start from vertices with in-degree == 0
    FOR(i,1,n) FOR(j,1,n) if (to[i][j].first > 0 && res[i][j] == 0) {

        int x = i, y = j;
        while (x > 0 && y > 0 && res[x][y] == 0) {
            int u = from[x][y].first;
            int v = from[x][y].second;

            if (u < 0) break;
            if (res[u][v]) break;

            res[x][y] = 1;
            res[u][v] = 2;

            x = from[u][v].first;
            y = from[u][v].second;
        }
    }

    // start from any vertex
    FOR(i,1,n) FOR(j,1,n) if (res[i][j] == 0 && from[i][j].first > 0) {
        int x = i, y = j;
        while (x > 0 && y > 0 && res[x][y] == 0) {
            int u = from[x][y].first;
            int v = from[x][y].second;

            if (u < 0) break;
            if (res[u][v]) break;
            if (res[x][y]) break;

            res[x][y] = 1;
            res[u][v] = 2;

            x = from[u][v].first;
            y = from[u][v].second;
        }
    }

    FOR(i,1,n) FOR(j,1,n) if (a[i][j] == '1' && res[i][j] == 0) return 0;
    return 1;
}

#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("divide.in", "r", stdin);
    freopen("divide.out", "w", stdout);

    while (cin >> n) {
        FOR(i,1,n) FOR(j,1,n) cin >> a[i][j];
        FOR(i,1,n) FOR(j,1,n) rot[i][j] = make_pair(i, j);

        try {
            REP(r,4) {
                FOR(di,-20,20) FOR(dj,-20,20) {
                    memset(to, -1, sizeof to);
                    memset(from, -1, sizeof from);

                    FOR(i,1,n) FOR(j,1,n) if (a[i][j] == '1') {
                        int u = rot[i][j].first + di;
                        int v = rot[i][j].second + dj;

                        if (u == i && v == j) continue;

                        if (inside(u, v) && a[u][v] == '1') {
                            from[i][j] = make_pair(u, v);
                            to[u][v] = make_pair(i, j);
                        }
                    }
                    if (check()) {
                        throw 1;
                    }
                }
                FOR(i,1,n) FOR(j,1,n) rot[i][j] = rotate(rot[i][j].first, rot[i][j].second);
            }
            cout << "NO" << endl;
        } catch (...) {
            cout << "YES" << endl;

            FOR(i,1,n) {
                FOR(j,1,n) {
                    if (res[i][j] == 1) cout << 1;
                    else cout << 0;
                }
                cout << endl;
            }
        }
    }
}
