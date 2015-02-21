
#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define left __left
#define right __right
using namespace std;

vector< vector<char> > a, savea;
vector< vector<int> > up, down, left, right;

#define init(X) { X.resize(m+5); REP(i,m+5) X[i].resize(n+5); }
int m, n, cur[5011];
char tmp[100111];

void calc() {
    // up
    memset(cur, 0, sizeof cur);
    FOR(i,1,m) {
        FOR(j,1,n) if (a[i][j] != '.') {
            if (cur[j]) up[i][j] = cur[j];
            cur[j] = i;
        }
    }
    // down
    memset(cur, 0, sizeof cur);
    FORD(i,m,1) {
        FOR(j,1,n) if (a[i][j] != '.') {
            if (cur[j]) down[i][j] = cur[j];
            cur[j] = i;
        }
    }
    // left
    memset(cur, 0, sizeof cur);
    FOR(j,1,n) {
        FOR(i,1,m) if (a[i][j] != '.') {
            if (cur[i]) left[i][j] = cur[i];
            cur[i] = j;
        }
    }
    // right
    memset(cur, 0, sizeof cur);
    FORD(j,n,1) {
        FOR(i,1,m) if (a[i][j] != '.') {
            if (cur[i]) right[i][j] = cur[i];
            cur[i] = j;
        }
    }
}

void clear(int u, int v) {
    int x = up[u][v], y = down[u][v];
    if (x) down[x][v] = y;
    if (y) up[y][v] = x;

    x = left[u][v], y = right[u][v];
    if (x) right[u][x] = y;
    if (y) left[u][y] = x;
    a[u][v] = '.';
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        init(a); init(savea);
        init(up); init(down); init(left); init(right);

        FOR(i,1,m) {
            gets(tmp);
            FOR(j,1,n) a[i][j] = savea[i][j] = tmp[j-1];
        }
        calc();

//        FOR(i,1,m) PR(a[i], n);
//        FOR(i,1,m) PR(up[i], n);
//        FOR(i,1,m) PR(down[i], n);
//        FOR(i,1,m) PR(left[i], n);
//        FOR(i,1,m) PR(right[i], n);

        int res = 0, cnt = 0;
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] != '.') {
            int u = i, v = j;
            int cur = 0;
            while (true) {
                ++cur;
                if (a[u][v] == 'U') {
                    if (!up[u][v]) break;
                    else {
                        clear(u, v);
                        u = up[u][v];
                    }
                }
                else if (a[u][v] == 'D') {
                    if (!down[u][v]) break;
                    else {
                        clear(u, v);
                        u = down[u][v];
                    }
                }
                else if (a[u][v] == 'L') {
                    if (!left[u][v]) break;
                    else {
                        clear(u, v);
                        v = left[u][v];
                    }
                }
                else {
                    if (!right[u][v]) break;
                    else {
                        clear(u, v);
                        v = right[u][v];
                    }
                }
            }

            if (cur > res) {
                res = cur;
                cnt = 1;
            }
            else if (cur == res) ++cnt;

            FOR(i,1,m) FOR(j,1,n) a[i][j] = savea[i][j];
            calc();
        }

        cout << res << ' ' << cnt << endl;
    }
    return 0;
}
