//#pragma comment(linker, "/STACK:66777216")
#include <iomanip>
#include <sstream>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>
#include <bitset>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i<_a; ++i)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
#define DEBUG(x) cout << #x << " = " << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(i,1,n) cout << a[i] << ' '; puts("");
#define PR0(a,n) cout << #a << " = "; REP(i,n) cout << a[i] << ' '; puts("");
using namespace std;

const double PI = acos(-1.0);

int m, n;
char a[55][55];
int qu[55*55], qv[55*55], first, last;

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

bool mark[55][55];

bool check() {
    memset(mark, false, sizeof mark);
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '#') {
        first = last = 1;
        qu[1] = i; qv[1] = j;
        mark[i][j] = true;
        
        while (first <= last) {
            int u = qu[first], v = qv[first]; ++first;
            REP(dir,4) {
                int uu = u + di[dir], vv = v + dj[dir];
                if (a[uu][vv] == '#' && !mark[uu][vv]) {
                    mark[uu][vv] = true;
                    ++last;
                    qu[last] = uu;
                    qv[last] = vv;
                }
            }
        }
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '#' && !mark[i][j]) return true;
        return false;
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    while (scanf("%d%d\n", &m, &n) == 2) {
        int cnt = 0;
        FOR(i,1,m) {
            scanf("%s\n", &a[i][1]);
            FOR(j,1,n) if (a[i][j] == '#') ++cnt;
        }
        if (cnt < 3) {
            puts("-1");
            continue;
        }
        bool ok = false;
        FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '#') {
            if (ok) break;
            a[i][j] = '.';
            if (check()) ok = true;
            a[i][j] = '#';
        }
        if (ok) puts("1");
        else puts("2");
    }
    return 0;
}
