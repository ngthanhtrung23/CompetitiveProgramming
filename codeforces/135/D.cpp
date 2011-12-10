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

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair
using namespace std;

const double PI = acos(-1.0);
const int MAXN = 1000111;

int m, n, res = 0, first, last;
char a[1011][1011];
int mark[1011][1011];
int qu[MAXN], qv[MAXN];
int listu[MAXN], listv[MAXN], listn;

int mark1[1011][1011];

const int di[] = {-1,-1,-1,0,0,1,1,1};
const int dj[] = {-1,0,1,-1,1,-1,0,1};
const int dt[] = {0,1,0,1,1,0,1,0};

void bfs(int startu, int startv, int cur) {
    listn = 0;
    first = last = 1;
    qu[1] = startu; qv[1] = startv;
    
    mark[startu][startv] = cur;
    
    int outside = 0;
    
    while (first <= last) {
        int u = qu[first], v = qv[first++];
        REP(dir,8) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu > m || uu < 1 || vv > n || vv < 1) continue;
            
            if ((uu == 1 || uu == m || vv == 1 || vv == n) && a[uu][vv] == '0') outside = 1;
            
            if (a[uu][vv] == '0') {
                if (mark[uu][vv] == 0) {
                    qu[++last] = uu; qv[last] = vv;
                }
            }
            else {
                if (mark[uu][vv] != cur) {
                    listn++;
                    listu[listn] = uu;
                    listv[listn] = vv;
                }
            }
            mark[uu][vv] = cur;
        }
    }
    
    if (outside) return ;
    
//    FOR(i,1,listn) cout << listu[i] << ' ' << listv[i] << ' ' << mark[listu[i]][listv[i]] << endl;
    
    FOR(i,1,listn) {
        int u = listu[i], v = listv[i];
        int cnt = 0;
        REP(dir, 8) if (dt[dir] == 1) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (a[uu][vv] == '1' && mark[uu][vv] == cur) cnt++;
        }
        if (cnt != 2) return ;
        if (mark1[u][v] != mark1[listu[1]][listv[1]]) return ;
    }
    res = max(res, listn);
}

void bfs1(int i, int j, int _) {
    first = last = 1;
    qu[1] = i; qv[1] = j;
    mark1[i][j] = _;
    
    while (first <= last) {
        int u = qu[first], v = qv[first]; first++;
        REP(dir,8) if (dt[dir] == 1) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu > m || uu < 1 || vv > n || vv < 1) continue;
            if (a[uu][vv] != '1') continue;
            
            if (!mark1[uu][vv]) {
                mark1[uu][vv] = _;
                last++;
                qu[last] = uu; qv[last] = vv;
            }
        }
    }
}

int main() {
//    freopen("input.txt", "r", stdin);
//    freopen("output.txt", "w", stdout);
    // Input
    scanf("%d %d\n", &m, &n);
    FOR(i,1,m) scanf("%s\n", &a[i][1]);
    
    int _ = 0;
    FOR(i,1,m) FOR(j,1,n)
        if (a[i][j] == '1' && mark1[i][j] == 0) {
            bfs1(i, j, ++_);
        }
    
    // Boring
    FOR(i,1,m) FOR(j,1,n)
        if (a[i][j] == '1' && a[i+1][j] == '1' && a[i][j+1] == '1' && a[i+1][j+1] == '1')
            res = 4;
    
    // bfs
    int cur = 0;
    FOR(i,1,m) FOR(j,1,n) if (a[i][j] == '0' && mark[i][j] == 0) {
        bfs(i, j, ++cur);
    }
    printf("%d\n", res);
    return 0;
}
