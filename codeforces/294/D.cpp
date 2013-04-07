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
const int MN = 200111;

int cnt[2][MN], m, n, nId[2];
map< pair<int,int>, int > id[2];
map< pair<int,int>, pair<int,int> > to[2];
set< pair<int,int> > visited;
int sum[2][MN];

int get(int t, int u) {
    int res = 0;
    while (u > 0) {
        res += sum[t][u];
        u -= u & (-u);
    }
    return res;
}

void update(int t, int u) {
    while (u <= nId[t]) {
        sum[t][u]++;
        u += u & (-u);
    }
}

void init() {
    visited.clear();
    memset(cnt, 0, sizeof cnt);
    memset(sum, 0, sizeof sum);
    to[0].clear(); to[1].clear();
    id[0].clear(); id[1].clear();
    nId[0] = nId[1] = 0;

    FOR(diff,1-n,m-1) {
        int i = 1, j = i - diff;
        if (j < 1) {
            j = 1;
            i = j + diff;
        }
        // cout << i << ' ' << j << "   ";
        id[0][make_pair(i, j)] = ++nId[0];
        int savei = i, savej = j;

        i = m, j = i - diff;
        if (j > n) {
            j = n;
            i = j + diff;
        }
        // cout << i << ' ' << j << endl;
        id[0][make_pair(i, j)] = nId[0];

        to[0][make_pair(i, j)] = make_pair(savei, savej);
        to[0][make_pair(savei, savej)] = make_pair(i, j);
    }

    FOR(sum,2,m+n) {
        int i = 1, j = sum - i;
        if (j > n) {
            j = n;
            i = sum - j;
        }

        id[1][make_pair(i, j)] = ++nId[1];
        // cout << i << ' ' << j << "   ";
        int savei = i, savej = j;

        i = m, j = sum - i;
        if (j < 1) {
            j = 1;
            i = sum - j;
        }

        id[1][make_pair(i, j)] = nId[1];
        // cout << i << ' ' << j << endl;

        to[1][make_pair(i, j)] = make_pair(savei, savej);
        to[1][make_pair(savei, savej)] = make_pair(i, j);
    }
}

int main() {
    while (cin >> m >> n) {
        init();
        int u, v; string tmp;
        cin >> u >> v >> tmp;

        int dir;
        if (tmp == "DR") {
            if (u == 1 || v == 1) dir = 0;
            else dir = 1;
        }

        if (tmp == "UL") {
            if (u == m || v == n) dir = 0;
            else dir = 1;
        }

        if (tmp == "DL") {
            if (u == 1 || v == n) dir = 1;
            else dir = 0;
        }

        if (tmp == "UR") {
            if (u == m || v == 1) dir = 1;
            else dir = 0;
        }

        long long res = 0;
        long long cur = 0;
        long long all = 0;
        if (m % 2 == 0 || n % 2 == 0) all = m * (long long) n / 2;
        else {
            all = m * (long long) n / 2;
            if (u % 2 == 1 && v % 2 == 1) all++;
        }

        // DEBUG(all);

        while (true) {
            int uu = to[dir][make_pair(u, v)].first;
            int vv = to[dir][make_pair(u, v)].second;
            if (u == uu && v == vv) {
                dir = 1 - dir;
                continue;
            }

            int len = (abs(u - uu) + abs(v - vv)) / 2 + 1;

            int k1 = id[1-dir][make_pair(u, v)];
            int k2 = id[1-dir][make_pair(uu, vv)];

            int has = get(1-dir, max(k1, k2) - 1) - get(1-dir, min(k1, k2));

            if (visited.find(make_pair(u, v)) != visited.end())
                ++has;
            if (make_pair(u, v) != make_pair(uu, vv)
                    && visited.find(make_pair(uu, vv)) != visited.end())
                ++has;

            int t = id[dir][make_pair(uu, vv)];
            if (cnt[dir][t] == 4) {
                res = -1;
                break;
            }
            ++cnt[dir][t];
            if (cnt[dir][t] > 1) has = len;


            if (res == 0) res += len;
            else res += len - 1;

            cur = cur + len - has;
            if (cur == all) break;

            // DEBUG(cur);

            if (make_pair(u, v) != make_pair(uu, vv)) {
                if (get(dir, t) - get(dir, t-1) == 0)
                update(dir, t);
            }

            dir = 1 - dir;
            visited.insert(make_pair(u, v));
            visited.insert(make_pair(uu, vv));
            u = uu; v = vv;
        }
        cout << res << endl;
        // cout << endl;
    }
    return 0;
}
