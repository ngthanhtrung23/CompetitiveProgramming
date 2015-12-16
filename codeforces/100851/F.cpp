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

const int MN = 1011;
double w;
int n;
double savex, savey;
double c[MN][MN], x[MN], y[MN];

int tru[2][MN], trt[2][MN];

bool check(double r) {
    queue<int> qu;
    queue<int> qt;
    qu.push(0);
    qt.push(0);
    memset(tru, -1, sizeof tru);
    tru[0][0] = trt[0][0] = 0;

    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        int t = qt.front(); qt.pop();

        if (u == n+1 && t == 1) return true;

        FOR(v,1,n+1) {
            // (u, t) --> (v, t)
            if (c[u][v] <= r && tru[t][v] < 0) {
                tru[t][v] = u;
                trt[t][v] = t;
                qu.push(v);
                qt.push(t);
            }

            if (t == 1) continue;
            if (c[u][v] <= r+r && tru[1][v] < 0) {
                tru[1][v] = u;
                trt[1][v] = t;
                qu.push(v);
                qt.push(1);
            }
        }
    }
    return false;
}

bool found;
void trace(int v, int t2) {
    if (v == 0) return ;

    int u = tru[t2][v];
    int t = trt[t2][v];

    if (t == 0 && t2 == 1) {
        if (u == 0) {
            savex = x[v] / 2.0;
            savey = y[v];
        }
        else if (v == n+1) {
            savex = (w + x[u]) / 2.0;
            savey = y[u];
        }
        else {
            savex = (x[u] + x[v]) / 2.0;
            savey = (y[u] + y[v]) / 2.0;
        }
        found = true;
        return ;
    }

    trace(u, t);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    freopen("froggy.in", "r", stdin);
    freopen("froggy.out", "w", stdout);
    while (cin >> w >> n) {
        if (n == 0) {
            cout << w / (double) 2.0 << ' ' << 0 << endl;
            continue;
        }
        FOR(i,1,n) cin >> x[i] >> y[i];

        FOR(i,1,n) FOR(j,1,n)
            c[i][j] = sqrt(sqr(x[i] - x[j]) + sqr(y[i] - y[j]));

        FOR(i,1,n) c[0][i] = c[i][0] = x[i];
        FOR(i,1,n) c[i][n+1] = c[n+1][i] = w - x[i];
        c[0][n+1] = c[n+1][0] = w;

        double l = 0.0, r = w;
        REP(turn,100) {
            double mid = (l + r) / 2.0;
            if (check(mid)) r = mid;
            else l = mid;
        }
        check(r);
        found = false;
        trace(n+1, 1);
        if (!found) {
            savex = w / 2.0;
            savey = 0;
        }
        cout << savex << ' ' << savey << endl;
    }
}
