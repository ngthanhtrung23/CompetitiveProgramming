#define _GLIBCXX_DEBUG
#include <sstream>
#include <iomanip>
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
#define FORN(i,a,b) for(int i=(a),_b=(b);i<_b;i++)
#define DOWN(i,a,b) for(int i=a,_b=(b);i>=_b;i--)
#define SET(a,v) memset(a,v,sizeof(a))
#define sqr(x) ((x)*(x))
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (REACHEOF) return 0;\
        memset(BUF,0,sizeof BUF);\
        int inpzzz = fread(BUF,1,BUFSIZE,stdin);\
        if (inpzzz != BUFSIZE) REACHEOF = true;\
        inp=BUF; \
    } \
    INP=*inp++; \
}
#define DIG(a) (((a)>='0')&&((a)<='9'))
#define GN(j) { \
    AM=0;\
    GETCHAR(INP); while(!DIG(INP) && INP!='-') GETCHAR(INP);\
    if (INP=='-') {AM=1;GETCHAR(INP);} \
    j=INP-'0'; GETCHAR(INP); \
    while(DIG(INP)){j=10*j+(INP-'0');GETCHAR(INP);} \
    if (AM) j=-j;\
}
//End of buffer reading

const long double PI = acos((long double) -1.0);

map< pair<int,int>, bool > visited;
map< pair<int,int>, int > d;

void mark(int x, int y, int v) {
    visited[MP(x, y)] = true;
    d[MP(x, y)] = v;
}

const int dx[] = {1, 0, -1, 0};
const int dy[] = {0, 1, 0, -1};

void init() {
    mark(0, 0, 0);
    mark(1, 0, 0);
    mark(1, 1, 1);
    mark(0, 1, 2);
    int x = 0, y = 1;
    int dir = 2;
    int now = 2;
    while (abs(x) < 150) {
        int nextDir = (dir + 1) % 4;
        if (visited.find(MP(x + dx[nextDir], y + dy[nextDir])) == visited.end()) {
            dir = nextDir;
            x = x + dx[dir], y = y + dy[dir];
            ++now;
        }
        else {
            x += dx[dir]; y += dy[dir];
        }
        mark(x, y, now);
    }
}

int main() {
    init();
    int x, y;
    while (cin >> x >> y) {
        cout << d[MP(x, y)] << endl;
    }
    return 0;
}
