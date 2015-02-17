
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

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};
const string from = "v^><";
const string to = "^v<>";

int m, n;
char a[2011][2011], tmp[2011];
int deg[2011][2011];

void solve() {
    queue< pair<int,int> > s;
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '.') {
        int cnt = 0;
        REP(dir,4) {
            if (a[i+di[dir]][j+dj[dir]] == '.') {
                ++cnt;
            }
        }
        deg[i][j] = cnt;
        if (cnt == 1) s.push(make_pair(i, j));
    }

    while (!s.empty()) {
        auto cur = s.front(); s.pop();
        int i = cur.first, j = cur.second;
        if (a[i][j] != '.') continue;

        REP(dir,4) {
            int ii = i + di[dir], jj = j + dj[dir];
            if (a[ii][jj] == '.') {
                a[i][j] = from[dir];
                a[ii][jj] = to[dir];

                REP(dir2,4) {
                    int u = ii + di[dir2], v = jj + dj[dir2];
                    if (a[u][v] == '.') {
                        --deg[u][v];
                        if (deg[u][v] == 1) {
                            s.push(make_pair(u, v));
                        }
                    }
                }

                break;
            }
        }
    }

    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '.') {
        cout << "Not unique" << endl;
        return ;
    }

    FOR(i,1,m) {
        FOR(j,1,n) putchar(a[i][j]);
        puts("");
    }
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        memset(a, 0, sizeof a);
        FOR(i,1,m) {
            gets(tmp);
            FOR(j,1,n) a[i][j] = tmp[j-1];
        }
        solve();
    }
    return 0;
}
