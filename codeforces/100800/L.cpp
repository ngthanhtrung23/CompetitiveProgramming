
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(X) ((int) ((X).size()))
using namespace std;

const int MN = 1011;

int n, r, c;
int a[MN][MN];

int get(char c) {
    if (c >= '0' && c <= '9') return c - '0';
    return c - 'A' + 10;
}

int mp[66000];
int visited[MN][MN], b[MN][MN];

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

void dfs(int u, int v) {
    visited[u][v] = 1;
    REP(dir,4) {
        int uu = u + di[dir], vv = v + dj[dir];
        if (b[uu][vv] && !visited[uu][vv]) {
            dfs(uu, vv);
        }
    }
}

int getA(int i, int j) {
    if (i < 1 || i > r || j < 1 || j > c) return 0;
    return a[i][j];
}

int getB(int i, int j) {
    if (i < 1 || i > r || j < 1 || j > c) return 0;
    return b[i][j];
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> r >> c) {
        FOR(i,1,r) FOR(j,1,c) {
            string s; cin >> s;
            a[i][j] = get(s[0]) * 16 * 16 * 16
                    + get(s[1]) * 16 * 16
                    + get(s[2]) * 16
                    + get(s[3]);
        }
        FOR(i,0,n*n) {
            int sum = i * 65535;
            mp[sum / (n*n)] = i;
        }
        FOR(i,1,r) FOR(j,1,c) a[i][j] = mp[a[i][j]];

        int k = n / 2;
        FOR(i,1,r) FOR(j,1,c) {
            b[i][j] = getA(i-k, j-k)
                - getA(i-k, j-k-1)
                - getA(i-k-1, j-k)
                + getA(i-k-1, j-k-1)
                - getB(i-n, j-n)
                + getB(i-n, j)
                + getB(i, j-n);
        }

//        FOR(i,1,r) {
//            PR(b[i], c);
//        }

        memset(visited, 0, sizeof visited);
        int res = 0;
        FOR(i,1,r) FOR(j,1,c) if (!visited[i][j] && b[i][j] == 1) {
            visited[i][j] = 1;
            dfs(i, j);
            ++res;
        }
        cout << res << endl;
    }
}

