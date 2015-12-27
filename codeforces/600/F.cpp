
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

int nLeft, nRight, m;
int usedLeft[MN][MN], usedRight[MN][MN];
int degLeft[MN], degRight[MN];

pair<int,int> edges[MN*MN];
int res[MN][MN];

void uncolor(int u, int v, int c) {
    assert(usedLeft[u][c] == v);
    assert(usedRight[v][c] == u);
    usedLeft[u][c] = 0;
    usedRight[v][c] = 0;
}

void color(int u, int v, int c) {
    assert(!usedLeft[u][c]);
    assert(!usedRight[v][c]);

    usedLeft[u][c] = v;
    usedRight[v][c] = u;

    res[u][v] = c;
}

// recolor edge (u, v) from color c1 to color c2
void recolor(int u, int v, int c1, int c2) {
    uncolor(u, v, c1);

    if (usedRight[v][c2]) {
        int uu = usedRight[v][c2];
        recolor(uu, v, c2, c1);

        color(u, v, c2);
    }
    else if (usedLeft[u][c2]) {
        int vv = usedLeft[u][c2];
        recolor(u, vv, c2, c1);

        color(u, v, c2);
    }
    else {
        color(u, v, c2);
    }
}

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    while (scanf("%d%d%d", &nLeft, &nRight, &m) == 3) {
        memset(degLeft, 0, sizeof degLeft);
        memset(degRight, 0, sizeof degRight);
        int D = 0;
        FOR(i,1,m) {
            int u, v; scanf("%d%d", &u, &v);
            edges[i] = make_pair(u, v);

            degLeft[u]++;
            degRight[v]++;
            D = max(D, degLeft[u]);
            D = max(D, degRight[v]);
        }
        printf("%d\n", D);
        FOR(i,1,m) {
            int u = edges[i].first, v = edges[i].second;
            // if there is some color C, that is not used in both u and v
            bool ok = false;
            FOR(c,1,D) {
                if (!usedLeft[u][c] && !usedRight[v][c]) {
                    ok = true;
                    color(u, v, c);
                    break;
                }
            }
            if (ok) continue;

            int c1 = -1, c2 = -1;
            FOR(c,1,D) {
                if (usedLeft[u][c] && !usedRight[v][c]) {
                    c1 = c;
                    break;
                }
            }
            FOR(c,1,D) {
                if (!usedLeft[u][c] && usedRight[v][c]) {
                    c2 = c;
                    break;
                }
            }

            recolor(u, usedLeft[u][c1], c1, c2);
            color(u, v, c1);
        }

        FOR(i,1,m) {
            int u = edges[i].first, v = edges[i].second;
            printf("%d ", res[u][v]);
        }
        puts("");
    }
}
