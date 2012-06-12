#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string>
#include <vector>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <iomanip>
#include <bitset>
#include <complex>

#define FOR(i,a,b) for(int i = a; i <= b; ++i)
#define FORD(i,a,b) for(int i = a; i >= b; --i)
#define REP(i,a) for(int i = 0; i < a; ++i)
#define MP make_pair
#define PB push_back
#define F first
#define S second
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(x,n) cout << #x << " = "; FOR(__,1,n) cout << x[__] << ' '; puts("");
#define PR0(x,n) cout << #x << " = "; REP(__,n) cout << x[__] << ' '; puts("");
using namespace std;

const int MN = 1511;
const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

int m, n;
pair<int,int> qu[MN*MN], mark[MN][MN];
char a[MN][MN];
bool visited[MN][MN];

bool check() {
    memset(visited, false, sizeof visited);

    int first = 1, last = 1;
    REP(i,m) REP(j,n) if (a[i][j] == 'S') {
        qu[1] = MP(i,j);
        visited[i][j] = true;
        mark[i][j] = MP(i,j);
    }

    while (first <= last) {
        pair<int,int> u, v, w;
        u = qu[first++];
        REP(dir,4) {
            v = MP(u.F + di[dir], u.S + dj[dir]);
            w = MP((v.F % m + m) % m, (v.S % n + n) % n);

            if (a[w.F][w.S] == '#') continue;

            if (visited[w.F][w.S]) {
                if (mark[w.F][w.S] != v) {
                    return true;
                }
                continue;
            }
            visited[w.F][w.S] = true;
            mark[w.F][w.S] = v;
            qu[++last] = v;
        }
    }
    return false;
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        REP(i,m) gets(a[i]);
        if (check()) puts("Yes");
        else puts("No");
    }
    return 0;
}
