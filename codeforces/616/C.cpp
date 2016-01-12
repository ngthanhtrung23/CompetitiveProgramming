
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 2000111;

int lab[MN];
struct DSU {
    void init(int n) {
        REP(i,n+1) lab[i] = -1;
    }

    int getRoot(int u) {
        if (lab[u] < 0) return u;
        return lab[u] = getRoot(lab[u]);
    }

    bool merge(int u, int v) {
        u = getRoot(u); v = getRoot(v);
        if (u == v) return false;
        if (lab[u] > lab[v]) swap(u, v);
        lab[u] += lab[v];
        lab[v] = u;
        return true;
    }
};

int m, n;
char a[1011][1011];

const int di[4] = {-1,1,0,0};
const int dj[4] = {0,0,-1,1};

bool outside(int i, int j) {
    return i < 1 || i > m || j < 1 || j > n;
}

int id(int i, int j) {
    return (i-1) * n + j;
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &a[i][1]);
        DSU dsu;
        dsu.init((m+1) * (n+1));

        FOR(i,1,m) FOR(j,1,n) {
            REP(dir,4) {
                int ii = i + di[dir], jj = j + dj[dir];
                if (outside(ii, jj)) continue;

                if (a[i][j] == '*' || a[ii][jj] == '*') continue;

                dsu.merge(id(i, j), id(ii, jj));
            }
        }
        FOR(i,1,m) {
            FOR(j,1,n) {
                if (a[i][j] == '.') {
                    putchar('.');
                }
                else {
                    int res = 1;
                    set<int> all;
                    REP(dir,4) {
                        int ii = i + di[dir], jj = j + dj[dir];
                        if (outside(ii, jj)) continue;

                        if (a[ii][jj] == '*') continue;

                        int t = dsu.getRoot(id(ii, jj));
                        if (all.count(t)) continue;
                        all.insert(t);

                        res += -lab[dsu.getRoot(id(ii, jj))];
                    }
                    putchar((char) ('0' + res % 10));
                }
            }
            puts("");
        }
    }
}
