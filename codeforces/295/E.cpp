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

struct Query {
    int type, u, v;
} query[MN];

int x[MN], cur[MN], nPoint, nQuery, c[MN], nC;

void init() {
    nC = 0;
    FOR(i,1,nPoint) {
        cur[i] = x[i];
        c[++nC] = x[i];
    }
    FOR(i,1,nQuery) {
        if (query[i].type == 1) {
            cur[query[i].u] += query[i].v;
            c[++nC] = cur[query[i].u];
        }
    }

    sort(c+1, c+nC+1);
    nC = unique(c+1, c+nC+1) - c - 1;
}

long long sum[MN * 6], it[MN * 6], sz[MN * 6];
pair< pair<long long, long long>, long long> nodes[1011];
int nNode;

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

map<int,int> initial;

void update(int i) {
    sum[i] = sum[CT(i)] + sum[CP(i)];
    sz[i] = sz[CT(i)] + sz[CP(i)];

    it[i] = it[CT(i)] + it[CP(i)] + sum[CP(i)] * sz[CT(i)] - sum[CT(i)] * sz[CP(i)];
}

void build(int i, int l, int r) {
    if (l == r) {
        if (initial.find(c[l]) == initial.end()) {
            sum[i] = 0;
            sz[i] = 0;
        }
        else {
            sum[i] = initial[c[l]];
            sz[i] = 1;
        }
        it[i] = 0;
        return ;
    }

    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);

    update(i);
}

void get(int i, int l, int r, int u, int v) {
    if (v < c[l] || c[r] < u) return ;
    if (u <= c[l] && c[r] <= v) {
        nodes[++nNode] = MP(MP(sum[i], it[i]), sz[i]);
        return ;
    }
    int mid = (l + r) >> 1;
    get(CT(i), l, mid, u, v);
    get(CP(i), mid+1, r, u, v);
}

void remove(int i, int l, int r, int x) {
    if (x < c[l] || c[r] < x) return ;
    if (l == r) {
        if (sz[i]) {
            sz[i] = 0;
            sum[i] = 0;
            it[i] = 0;
        }
        return ;
    }
    int mid = (l + r) >> 1;
    remove(CT(i), l, mid, x);
    remove(CP(i), mid+1, r, x);

    update(i);
}

void add(int i, int l, int r, int x) {
    if (x < c[l] || c[r] < x) return ;
    if (l == r) {
        sz[i] = 1;
        sum[i] = x;
        it[i] = 0;
        return ;
    }
    int mid = (l + r) >> 1;
    add(CT(i), l, mid, x);
    add(CP(i), mid+1, r, x);

    update(i);
}

int main() {
    ios :: sync_with_stdio(false);
    while (scanf("%d", &nPoint) == 1) {
        memset(sum, 0, sizeof sum);
        memset(it, 0, sizeof it);

        FOR(i,1,nPoint) scanf("%d", &x[i]);
        scanf("%d", &nQuery);
        FOR(i,1,nQuery) {
            scanf("%d%d%d", &query[i].type, &query[i].u, &query[i].v);
        }
        init();

        initial.clear();
        FOR(i,1,nPoint) {
            initial[x[i]] = x[i];
            cur[i] = x[i];
        }

        build(1, 1, nC);

        FOR(i,1,nQuery) {
            if (query[i].type == 1) {
                remove(1, 1, nC, cur[query[i].u]);

                cur[query[i].u] += query[i].v;

                add(1, 1, nC, cur[query[i].u]);
            }
            else {
                nNode = 0;
                get(1, 1, nC, query[i].u, query[i].v);

                long long res = 0;
                long long curSum = 0, curIt = 0, curSz = 0;
                FOR(i,1,nNode) {
                    res += nodes[i].first.second;
                    res += nodes[i].first.first * curSz - curSum * nodes[i].second;

                    curSum += nodes[i].first.first;
                    curIt = res;
                    curSz += nodes[i].second;
                }
                cout << res << endl;
            }
        }
    }
    return 0;
}