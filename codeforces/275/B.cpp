#include <iostream>
#include <cmath>
#include <algorithm>
#include <cstdio>

#define FOR(i,a,b) for(int i=(a),_b=(b); i <= _b; ++i)
using namespace std;

char a[111][111];
int r[111][111], down[111][111];
int m, n;

bool check() {
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == 'B')
    FOR(u,i,m) FOR(v,1,n) if (a[u][v] == 'B') {
        int j1 = min(j, v), j2 = max(j, v);
        if (!(down[u][j] - down[i-1][j] == u - i + 1 && r[u][j2] - r[u][j1-1] == j2 - j1 + 1)
            && !(r[i][j2] - r[i][j1-1] == j2 - j1 + 1 && down[u][v] - down[i-1][v] == u - i + 1))
            return false;
    }
    return true;
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        FOR(i,1,m) scanf("%s\n", &a[i][1]);

        FOR(i,1,m) FOR(j,1,n) {
            down[i][j] = down[i-1][j] + (a[i][j] == 'B' ? 1 : 0);
            r[i][j] = r[i][j-1] + (a[i][j] == 'B' ? 1 : 0);
        }
        if (check()) puts("YES");
        else puts("NO");
    }
}
