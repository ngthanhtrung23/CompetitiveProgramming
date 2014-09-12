#include <set>
#include <map>
#include <list>
#include <cmath>
#include <queue>
#include <stack>
#include <cstdio>
#include <string>
#include <vector>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iomanip>
#include <complex>
#include <iostream>
#include <algorithm>

#include <ctime>
#include <deque>
#include <bitset>
#include <cctype>
#include <utility>
#include <cassert>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
using namespace std;

char tmp[100111];
int s, pos[111], costEach[111], n;
int from[111], to[111];
int d[111][111][111];

int id[111][111], rowId[111*111], colId[111*111];

const int di[] = {-1, -1, 0, 0, 1, 1};
const int dj[] = {-1, 0, -1, 1, 0, 1};

inline bool inside(int u, int v) {
    return 1 <= u && u <= s && from[u] <= v && v <= to[v];
}

void init() {
    memset(d, -1, sizeof d);
    int half = (s + 1) / 2;
    from[1] = 1, to[1] = half;
    FOR(i,2,s) {
        if (i > (s+1) / 2) {
            from[i] = from[i-1] + 1;
            to[i] = to[i-1];
        } else {
            from[i] = from[i-1];
            to[i] = to[i-1] + 1;
        }
    }

    // PR(from, s);
    // PR(to, s);

    int now = 0;
    FOR(row,1,s) {
        FOR(col,from[row],to[row]) {
            ++now;
            id[row][col] = now;
            rowId[now] = row;
            colId[now] = col;
        }
    }
}

queue< pair<int,int> > q;
void bfs(int u, int v, int turn) {
    q.push(make_pair(u, v));
    d[turn][u][v] = 0;

    while (!q.empty()) {
        u = q.front().first, v = q.front().second; q.pop();
        REP(dir,6) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (!inside(uu, vv)) continue;
            if (d[turn][uu][vv] >= 0) continue;

            d[turn][uu][vv] = d[turn][u][v] + 1;
            q.push(make_pair(uu, vv));
        }
    }
}

int target[111], cost[111][111];
#define LL int
const int MAXV = 111;

typedef LL VD[MAXV + 5];
typedef LL VVD[MAXV + 5][MAXV + 5];
typedef int VI[MAXV + 5];
VI Lmate, Rmate;
 
LL MinCostMatching() {
    memset(Lmate, -1, sizeof Lmate);
    memset(Rmate, -1, sizeof Rmate);
    VD u = {0};
    VD v = {0};
    REP (i, n) {
        u[i] = cost[i][0];
        FOR (j, 1, n-1) u[i] = min(u[i], cost[i][j]);
    }
    REP (j, n) {
        v[j] = cost[0][j] - u[0];
        FOR (i, 1, n-1) v[j] = min(v[j], cost[i][j] - u[i]);
    }
    REP (i, n) Lmate[i] = Rmate[i] = -1;
    int mated = 0;
    REP (i, n) REP (j, n) {
        if (Rmate[j] != -1) continue;
        if (abs(cost[i][j] - u[i] - v[j]) == 0) {
            Lmate[i] = j;
            Rmate[j] = i;
            mated++;
            break;
        }
    }
    VD dist = {0};
    VI dad = {0};
    VI seen = {0};
    while (mated < n) {
        int s = 0;
        while (Lmate[s] != -1) s++;
        fill(dad, dad + n, -1);
        fill(seen, seen + n, 0);
        REP (k, n) dist[k] = cost[s][k] - u[s] - v[k];
        int j = 0;
        while (true) {
            j = -1;
            REP (k, n) {
                if (seen[k]) continue;
                if (j == -1 || dist[k] < dist[j]) j = k;
            }
            seen[j] = 1;
            if (Rmate[j] == -1) break;
            const int i = Rmate[j];
            REP (k, n) {
                if (seen[k]) continue;
                const LL new_dist = dist[j] + cost[i][k] - u[i] - v[k];
                if (dist[k] > new_dist) {
                    dist[k] = new_dist;
                    dad[k] = j;
                }
            }
        }
        REP (k, n) {
            if (k == j || !seen[k]) continue;
            const int i = Rmate[k];
            v[k] += dist[k] - dist[j];
            u[i] -= dist[k] - dist[j];
        }
        u[s] += dist[j];
        while (dad[j] >= 0) {
            const int d = dad[j];
            Rmate[j] = Rmate[d];
            Lmate[Rmate[j]] = j;
            j = d;
        }
        Rmate[j] = s;
        Lmate[s] = j;
        mated++;
    }
    LL value = 0;
    REP (i, n) value += cost[i][Lmate[i]];
    return value;
}

int solve() {
    n = s;
    int res = 1000111000;
    REP(turn,3) {
        int half = (s + 1) / 2;
        if (turn == 0) {
            FOR(i,1,n) target[i] = id[half][i];
        } else if (turn == 1) {
            FOR(i,1,n) target[i] = id[i][i];
        } else {
            FOR(i,1,n) target[i] = id[i][half];
        }

        FOR(i,1,n) FOR(j,1,n) {
            cost[i-1][j-1] = d[i][rowId[target[j]]][colId[target[j]]] * costEach[i];
        }
        res = min(res, MinCostMatching());
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; scanf("%d\n", &ntest);
    FOR(test,1,ntest) {
        gets(tmp);
        s = 0;
        istringstream ss1(tmp);
        while (ss1 >> pos[s+1]) ++s;

        gets(tmp);
        istringstream ss2(tmp);
        FOR(i,1,s) ss2 >> costEach[i];

        // PR(pos, s);
        // PR(costEach, s);

        init();

        FOR(i,1,s) {
            int u = rowId[pos[i]], v = colId[pos[i]];
            bfs(u, v, i);
        }

        cout << "Case #" << test << ": " << solve() << endl;
    }
    return 0;
}
