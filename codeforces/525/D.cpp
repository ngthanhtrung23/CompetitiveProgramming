
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

int m, n;
char a[2011][2011];

bool isBad(int i, int j) {
    if (a[i][j] != '*') return false;
    if (a[i-1][j-1] == '.' && a[i-1][j] == '.' && a[i][j-1] == '.') return true;
    if (a[i-1][j+1] == '.' && a[i-1][j] == '.' && a[i][j+1] == '.') return true;

    if (a[i+1][j-1] == '.' && a[i+1][j] == '.' && a[i][j-1] == '.') return true;
    if (a[i+1][j+1] == '.' && a[i+1][j] == '.' && a[i][j+1] == '.') return true;
    return false;
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &a[i][1]);

        queue< pair<int,int> > qu;
        FOR(i,1,m) FOR(j,1,n)
            if (isBad(i, j)) {
                qu.push(make_pair(i, j));
                a[i][j] = '.';
            }

        while (!qu.empty()) {
            int u = qu.front().first, v = qu.front().second;
            qu.pop();
            a[u][v] = '.';

            FOR(di,-1,1) FOR(dj,-1,1)
                if (isBad(u+di, v+dj)) {
                    qu.push(make_pair(u+di, v+dj));
                    a[u+di][v+dj] = '.';
                }
        }

        FOR(i,1,m) {
            FOR(j,1,n) putchar(a[i][j]);
            puts("");
        }
    }
    return 0;
}
