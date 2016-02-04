
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

const int MN = 511;
int n1, n2, m;
bitset<MN> ke1[MN], ke2[MN];
int id[MN], deg[MN];
char color[MN];
vector<int> ls[MN];

void init() {
    FOR(i,1,n1) {
        ke1[i].reset();
        ke2[i].reset();
        id[i] = 0;

        ls[i].clear();
    }
    memset(color, 0, sizeof color);
    memset(deg, 0, sizeof deg);
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (cin >> n1 >> m) {
        init();
        FOR(i,1,n1) ke1[i][i] = 1;
        FOR(i,1,m) {
            int u, v; cin >> u >> v;
            ke1[u][v] = 1;
            ke1[v][u] = 1;
        }

        n2 = 0;
        FOR(i,1,n1) if (id[i] == 0) {
            ++n2;
            FOR(j,i,n1) if (ke1[i] == ke1[j]) {
                ls[n2].push_back(j);
                id[j] = n2;
            }
        }
//        DEBUG(n2);
//        FOR(i,1,n2) PR0(ls[i], SZ(ls[i]));

        FOR(i,1,n1) FOR(j,i+1,n1) if (ke1[i][j]) {
            int u = id[i], v = id[j];
            if (ke2[u][v] == 1) continue;
            if (u == v) continue;

            ke2[u][v] = ke2[v][u] = 1;
            ++deg[u];
            ++deg[v];
        }

//        PR(deg, n2);

        try {
            FOR(i,1,n2) if (deg[i] > 2) throw 1;

            char cur = 'a';
            FOR(i,1,n2) if (!color[i] && deg[i] <= 1) {
                color[i] = cur;
                int x = i;
                while (true) {
                    bool good = false;
                    FOR(j,1,n2) if (!color[j] && ke2[x][j]) {
                        x = j;
                        color[j] = ++cur;
                        good = true;
                    }
                    if (!good) break;
                }
                cur += 2;
            }
            FOR(i,1,n2) if (!color[i] || color[i] > 'c') throw 1;
            FOR(i,1,n1) {
                if (!color[id[i]]) throw 1;
            }
            cout << "Yes" << endl;
            FOR(i,1,n1) cout << color[id[i]]; cout << endl;
        } catch (int e) {
            cout << "No" << endl;
        }
    }
}
