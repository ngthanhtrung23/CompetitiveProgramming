
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
using namespace std;

const int MN = 1011;
int m, n;
bool a[MN][MN];
bool pieces[MN][MN];

pair<int,int> queens[MN], knights[MN];
int nQueen, nKnight, nPawn;

bool inside(int u, int v) {
    return u > 0 && u <= m && v > 0 && v <= n;
}

int main() {
    ios :: sync_with_stdio(false);
    int test = 0;
    while (cin >> m >> n && m && n) {
        FOR(i,1,m) FOR(j,1,n) a[i][j] = pieces[i][j] = false;

        cin >> nQueen;
        FOR(i,1,nQueen) {
            cin >> queens[i].first >> queens[i].second;
            pieces[queens[i].first][queens[i].second] = true;
        }
        cin >> nKnight;
        FOR(i,1,nKnight) {
            cin >> knights[i].first >> knights[i].second;
            pieces[knights[i].first][knights[i].second] = true;
        }
        cin >> nPawn;
        FOR(i,1,nPawn) {
            int u, v; cin >> u >> v;
            pieces[u][v] = true;
        }

        FOR(i,1,nKnight) {
            int u = knights[i].first, v = knights[i].second;
            FOR(di,-2,2) FOR(dj,-2,2) if (di*di + dj*dj == 5) {
                int uu = u + di, vv = v + dj;
                if (inside(uu, vv)) a[uu][vv] = true;
            }
        }

        FOR(i,1,nQueen) {
            FOR(di,-1,1) FOR(dj,-1,1) if (di || dj) {
                int u = queens[i].first, v = queens[i].second;
                while (true) {
                    u += di; v += dj;
                    if (!inside(u, v) || pieces[u][v]) break;

                    a[u][v] = true;
                }
            }
        }
        int cnt = 0;
        FOR(i,1,m) FOR(j,1,n) if (!a[i][j] && !pieces[i][j]) ++cnt;
        ++test;
        printf("Board %d has %d safe squares.\n", test, cnt);
    }
    return 0;
}

