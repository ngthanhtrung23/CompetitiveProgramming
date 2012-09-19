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
int INP,AM;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp) { \
        if (feof(stdin)) memset(BUF, 0, sizeof BUF); else fread(BUF,1,BUFSIZE,stdin); \
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

struct State {
    char a[15][15];
    int d;
} start;

int m, n;

bool operator < (const State &a, const State &b) {
    REP(i,m) REP(j,n)
        if (a.a[i][j] != b.a[i][j]) return a.a[i][j] < b.a[i][j];
    return false;
}

bool operator == (const State &a, const State &b) {
    REP(i,m) REP(j,n)
        if (a.a[i][j] != b.a[i][j]) return false;
    return true;
}

set<State> s;
set< pair<int, State> > q;

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

int first, last;
int qu[1011], qv[1011];
int mark[22][22];

inline int get(const State &a) {
    int res = a.d;
    int i1, i2, j1, j2;
    memset(mark, 0, sizeof mark);

    REP(i,m) REP(j,n) {
        if (a.a[i][j] == '1') i1 = i, j1 = j;
        else if (a.a[i][j] == '@') i2 = i, j2 = j;
    }
    first = last = 1;
    qu[1] = i1; qv[1] = j1;

    while (first <= last) {
        int u = qu[first], v = qv[first]; ++first;
        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu < 0 || uu >= m || vv < 0 || vv >= n) continue;
            if (mark[uu][vv]) continue;
            mark[uu][vv] = mark[u][v] + 1;
            if (a.a[uu][vv] == '@') return res + mark[uu][vv];
            if (a.a[uu][vv] == '#') continue;

            ++last;
            qu[last] = uu;
            qv[last] = vv;
        }
    }
    return 1000111000;
}

bool check() {
    first = last = 1;
    REP(i,m) REP(j,n) if (start.a[i][j] == '1') {
        qu[1] = i;
        qv[1] = j;
        mark[i][j] = true;
    }

    while (first <= last) {
        int u = qu[first], v = qv[first]; ++first;
        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu < 0 || uu >= m || vv < 0 || vv >= n) continue;
            if (mark[uu][vv]) continue;
            if (start.a[uu][vv] == '@') return true;
            if (start.a[uu][vv] == '#') continue;

            ++last;
            qu[last] = uu;
            qv[last] = vv;
            mark[uu][vv] = true;
        }
    }
    return false;
}

int main() {
    while (scanf("%d%d\n", &m, &n) == 2) {
        char ln = '1';
        REP(i,m) gets(start.a[i]);

        if (!check()) {
            puts("-1");
            return 0;
        }

        REP(i,m) REP(j,n)
            if (start.a[i][j] >= '0' && start.a[i][j] <= '9')
                ln = max(ln, start.a[i][j]);

        start.d = 0;
        q.insert(MP(get(start), start));
        s.insert(start);

        State u, v;
        while (!q.empty()) {
            u = q.begin()->S; q.erase(q.begin());
            v = u; ++v.d;

            // Remove tail
            int i2, j2;

            REP(i,m) REP(j,n) {
                if (v.a[i][j] == ln) v.a[i][j] = '.';
                else if (v.a[i][j] >= '1' && v.a[i][j] < ln) v.a[i][j]++;

                if (v.a[i][j] == '2') i2 = i, j2 = j;
            }

            // Add head
            REP(dir,4) {
                int uu = i2 + di[dir], vv = j2 + dj[dir];
                if (uu < 0 || vv < 0 || uu >= m || vv >= n) continue;
                if (v.a[uu][vv] == '@') {
                    printf("%d\n", v.d);
                    return 0;
                }
                if (v.a[uu][vv] == '.') {
                    v.a[uu][vv] = '1';
                    if (s.find(v) == s.end()) {
                        s.insert(v);
                        q.insert(MP(get(v), v));
                    }
                    v.a[uu][vv] = '.';
                }
            }
        }
    }
    puts("-1");
    return 0;
}
