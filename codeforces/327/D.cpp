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

const int MN = 511;
int first, last, qu[MN*MN], qv[MN*MN];
bool visited[MN][MN];
char a[MN][MN];
int m, n;
vector< pair<char, pair<int,int> > > res;

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

void bfs(int u, int v) {
    first = last = 1;
    qu[1] = u; qv[1] = v;
    visited[u][v] = true;
    while (first <= last) {
        u = qu[first]; v = qv[first]; ++first;

        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (a[uu][vv] == '.' && !visited[uu][vv]) {
                ++last;
                qu[last] = uu;
                qv[last] = vv;
                visited[uu][vv] = true;
            }
        }
    }

    FOR(i,1,last) res.push_back(make_pair('B', make_pair(qu[i], qv[i])));
    FORD(i,last,2) {
        res.push_back(make_pair('D', make_pair(qu[i], qv[i])));
        res.push_back(make_pair('R', make_pair(qu[i], qv[i])));
    }
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        memset(a, ' ', sizeof a);
        FOR(i,1,m) scanf("%s\n", &a[i][1]);
        memset(visited, false, sizeof visited);
        res.clear();
        FOR(i,1,m) FOR(j,1,n) if (!visited[i][j] && a[i][j] == '.') {
            bfs(i, j);
        }
        printf("%d\n", res.size());
        for(auto x : res) printf("%c %d %d\n", x.first, x.second.first, x.second.second);
    }
    return 0;
}

