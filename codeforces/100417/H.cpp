
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

const int MN = 5011;

int a[MN], b[MN], na, nb, k;
int f[MN][MN];
int tr[MN][MN];
int used[MN];
int nexta[MN][MN], nextb[MN][MN];

void init(int na, int a[], int next[][MN]) {
    FORD(i,na+1,0) {
        if (i > na) {
            FOR(x,1,k) next[i][x] = na+1;
        }
        else if (i == na) {
            FOR(x,1,k) next[i][x] = na+1;
        }
        else {
            FOR(x,1,k) {
                if (a[i+1] == x) next[i][x] = i+1;
                else next[i][x] = next[i+1][x];
            }
        }
    }
}

void trace(int u, int v) {
    if (u == 0) return ;

    int uu = tr[u][v] / MN;
    int vv = tr[u][v] % MN;

    trace(uu, vv);

    FOR(x,1,k) {
        if (nexta[uu][x] == u && nextb[vv][x] == v) {
            cout << x << ' ';
            break;
        }
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    freopen("robots.in", "r", stdin);
    freopen("robots.out", "w", stdout);

    while (cin >> k) {
        cin >> na; FOR(i,1,na) cin >> a[i];
        cin >> nb; FOR(i,1,nb) cin >> b[i];

        memset(used, 0, sizeof used);
        FOR(i,1,na) used[a[i]] = 1;
        FOR(i,1,nb) used[b[i]] = 1;

        init(na, a, nexta);
        init(nb, b, nextb);

//        FOR(i,1,na) {
//            PR(nexta[i], k);
//        }

        try {
            memset(f, -1, sizeof f);
            f[0][0] = 0;
            queue<int> qu, qv;
            qu.push(0);
            qv.push(0);
            while (!qu.empty()) {
                int u = qu.front(); qu.pop();
                int v = qv.front(); qv.pop();

                if (u == na+1 && v == nb+1) {
                    cout << f[u][v] << endl;
                    trace(u, v);
                    throw 1;
                }

                FOR(x,1,k) {
                    int uu = nexta[u][x];
                    int vv = nextb[v][x];

                    if (f[uu][vv] < 0) {
                        f[uu][vv] = f[u][v] + 1;
                        tr[uu][vv] = u * MN + v;
                        qu.push(uu);
                        qv.push(vv);
                    }
                }
            }
        } catch (int e) {
            cout << endl;
        }
    }
}
