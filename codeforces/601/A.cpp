
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 411;

int c[MN][MN];
int n, m;
int f[2][MN][MN];
deque<int> qu, qv, qt;

void go0(int t, int u, int v, int l) {
    if (f[t][u][v] < 0) {
        f[t][u][v] = l;
        qt.push_front(t);
        qu.push_front(u);
        qv.push_front(v);
    }
}

void go1(int t, int u, int v, int l) {
    if (f[t][u][v] < 0) {
        f[t][u][v] = l + 1;
        qt.push_back(t);
        qu.push_back(u);
        qv.push_back(v);
    }
}

int solve() {
    while (!qu.empty()) qu.pop_front();
    while (!qv.empty()) qv.pop_front();
    while (!qt.empty()) qt.pop_front();

    qt.push_back(0);
    qu.push_back(1);
    qv.push_back(1);

    f[0][1][1] = 0;

    while (!qt.empty()) {
        int t = qt.front(); qt.pop_front();
        int u = qu.front(); qu.pop_front();
        int v = qv.front(); qv.pop_front();

        if (u == n && v == n) return f[t][u][v];

        int l = f[t][u][v];
        if (t == 0) {
            // move u
            if (u == n) {
                go1(1, u, v, l);
            }
            else {
                FOR(x,1,n) if (c[u][x] == 0) {
                    go1(1, x, v, l);
                }
            }
        }
        else {
            // move v
            if (v == n) {
                go0(0, u, v, l);
            }
            else {
                FOR(x,1,n) if (c[v][x] == 1) {
                    if (x != n && x == u) continue;
                    go0(0, u, x, l);
                }
            }
        }
    }
    return -1;
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    while (scanf("%d%d", &n, &m) == 2) {
        memset(c, 0, sizeof c);
        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            c[u][v] = c[v][u] = 1;
        }

        memset(f, -1, sizeof f);
        cout << solve() << endl;
    }
}
