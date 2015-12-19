
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

const int MN = 2011;
vector<int> ke[MN];
int n, m, A, B, C, D;
int tru[MN][MN], trv[MN][MN];

vector<int> res[2];
void go(int u, int v) {
    if (u == 0 && v == 0) return ;

    go(tru[u][v], trv[u][v]);
    if (u != tru[u][v]) res[0].push_back(u);
    if (v != trv[u][v]) res[1].push_back(v);
}

void solve() {
    queue<int> qu, qv;
    memset(tru, -1, sizeof tru);
    qu.push(0);
    qv.push(0);
    tru[0][0] = 0;
    trv[0][0] = 0;
    while (!qu.empty()) {
        int u = qu.front(); qu.pop();
        int v = qv.front(); qv.pop();

        if (u == B && v == D) {
            res[0].clear(); res[1].clear();
            go(B, D);
            cout << "YES" << endl;
            for(int x : res[0]) cout << x << ' '; cout << endl;
            for(int x : res[1]) cout << x << ' '; cout << endl;
            return ;
        }

        // (u, v) --> (u, vv)
        if (v != D) {
            auto it = upper_bound(ke[v].begin(), ke[v].end(), u);
            while (it != ke[v].end()) {
                int vv = *it;
                ++it;
                if (v == 0 && vv != C) continue;
                if (tru[u][vv] < 0) {
                    tru[u][vv] = u;
                    trv[u][vv] = v;
                    qu.push(u);
                    qv.push(vv);
                }
            }
        }
        
        // (u, v) --> (uu, v)
        if (u != B) {
            auto it = upper_bound(ke[u].begin(), ke[u].end(), v);
            while (it != ke[u].end()) {
                int uu = *it;
                ++it;
                if (u == 0 && uu != A) continue;
                if (tru[uu][v] < 0) {
                    tru[uu][v] = u;
                    trv[uu][v] = v;
                    qu.push(uu);
                    qv.push(v);
                }
            }
        }
    }
    cout << "NO" << endl;
}

int main() {
    freopen("express.in", "r", stdin);
    freopen("express.out", "w", stdout);

    while (scanf("%d%d", &n, &m) == 2) {
        scanf("%d%d%d%d", &A, &B, &C, &D);
        if (A > B) swap(A, B);
        if (C > D) swap(C, D);

        FOR(i,0,n) ke[i].clear();
        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            ke[u].push_back(v);
        }
        ke[0].push_back(A);
        ke[0].push_back(C);
        FOR(i,0,n) {
            sort(ke[i].begin(), ke[i].end());
            ke[i].resize(unique(ke[i].begin(), ke[i].end()) - ke[i].begin());
        }
        solve();
    }
}
