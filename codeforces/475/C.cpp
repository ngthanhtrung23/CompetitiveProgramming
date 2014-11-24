#include <bits/stdc++.h>
using namespace std;

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)
#define SZ(S) ((int) ((S).size()))

#define DEBUG(x) { cout << #x << " = " << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

const int MN = 1011;
const int inf = 1000111000;
const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};
int m, n;
char a[MN][MN], b[MN][MN];
bool visited[MN][MN];
int first[MN][MN], last[MN][MN], sum[MN][MN];

void rotate() {
    FOR(i,1,m) FOR(j,1,n) b[i][j] = a[i][j];
    memset(a, ' ', sizeof a);
    swap(m, n);
    FOR(i,1,m) FOR(j,1,n) a[i][j] = b[j][i];
}

void init() {
    memset(sum, 0, sizeof sum);
    memset(first, 0, sizeof first);
    memset(last, 0, sizeof last);
    FOR(i,1,m) FOR(j,1,n) sum[i][j] = sum[i-1][j] + ((a[i][j] == 'X') ? 1 : 0);
    FOR(i,1,m) {
        FOR(j,1,n) 
            if (a[i][j] == 'X') {
                if (a[i-1][j] == 'X') first[i][j] = first[i-1][j];
                else first[i][j] = i;
            }
    }
    FORD(i,m,1) {
        FOR(j,1,n)
            if (a[i][j] == 'X') {
                if (a[i+1][j] == 'X') last[i][j] = last[i+1][j];
                else last[i][j] = i;
            }
    }
}

int check() {
    init();
    FOR(j,1,n) {
        FOR(i,1,m)
        if (a[i][j] == 'X') {
            if (sum[m][j] != last[i][j] - first[i][j] + 1)
                return inf;
            int height = sum[m][j];
            int i1 = i, i2 = i + height - 1;
            int j1 = j, j2 = j1;

            FOR(i,1,m) FOR(j,1,n) b[i][j] = a[i][j];

            bool canExtend = true;
            FOR(i,i1,i2) FOR(j,j1,j2) b[i][j] = '.';
            while (b[i1][j2+1] == 'X' || b[i2+1][j1] == 'X') {
                if (b[i1][j2+1] == 'X' && b[i2+1][j1] == 'X') {
                    // Extend right + go down
                    // so we extend right

                    if (!canExtend) return inf;
                    FOR(i,i1,i2) {
                        if (b[i][j2+1] == '.') return inf;
                        b[i][j2+1] = '.';
                    }
                    ++j2;
                }
                else if (b[i1][j2+1] == 'X') {
                    // Go right
                    FOR(i,i1,i2) {
                        if (b[i][j2+1] == '.') return inf;
                        b[i][j2+1] = '.';
                    }
                    ++j1; ++j2;
                }
                else {
                    // Go down
                    canExtend = false;
                    FOR(j,j1,j2) {
                        if (b[i2+1][j] == '.') return inf;
                        b[i2+1][j] = '.';
                    }
                    ++i1; ++i2;
                }
            }
            FOR(i,1,m) FOR(j,1,n) if (b[i][j] == 'X') return inf;
            return (i2 - i1 + 1) * (j2 - j1 + 1);
        }
    }
    return inf;
}

void solve() {
    memset(visited, false, sizeof visited);
    int components = 0;
    FOR(i,1,m) FOR(j,1,n) if (!visited[i][j] && a[i][j] == 'X') {
        ++components;
        if (components > 1) {
            cout << -1 << endl;
            return ;
        }
        queue< pair<int,int> > qu;
        qu.push(make_pair(i, j));
        visited[i][j] = true;
        while (!qu.empty()) {
            int u = qu.front().first, v = qu.front().second; qu.pop();
            REP(dir,4) {
                int uu = u + di[dir], vv = v + dj[dir];
                if (a[uu][vv] == 'X' && !visited[uu][vv]) {
                    qu.push(make_pair(uu, vv));
                    visited[uu][vv] = true;
                }
            }
        }
    }
    int res = inf;
    res = min(res, check());
    rotate();
    res = min(res, check());
    if (res == inf) res = -1;
    cout << res << endl;
}

int main() {
    ios :: sync_with_stdio(false); cin.tie(NULL);
    cout << (fixed) << setprecision(6);
    while (cin >> m >> n) {
        bool hasX = false;
        FOR(i,1,m) FOR(j,1,n) {
            cin >> a[i][j];
            if (a[i][j] == 'X') hasX = true;
        }
        if (!hasX) {
            cout << -1 << endl;
            continue;
        }
        solve();
    }
    return 0;
}
