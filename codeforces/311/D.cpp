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
const long long MOD = 95542721;

struct Node {
    int x[50];
    int rot;
} it[600111];

int n, a[100111];

#define sqr(x) ((x) * (ll)(x)) % MOD
#define cube(x) (sqr(x)) * (ll)(x) % MOD

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void build(int i, int l, int r) {
    if (l == r) {
        it[i].x[0] = a[l] % MOD;
        FOR(t,1,47) {
            it[i].x[t] = cube(it[i].x[t-1]);
        }
        it[i].rot = 0;
        return;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);

    REP(t,48) it[i].x[t] = (it[CT(i)].x[t] + it[CP(i)].x[t]) % MOD;
}

int save[55];

void down(int i, int l, int r) {
    if (it[i].rot == 0) return ;

    if (it[i].rot) {
        it[CT(i)].rot += it[i].rot; it[CT(i)].rot %= 48;
        it[CP(i)].rot += it[i].rot; it[CP(i)].rot %= 48;

        REP(t,48) save[t] = it[CT(i)].x[t];
        REP(t,48) it[CT(i)].x[t] = save[(t + it[i].rot) % 48];

        REP(t,48) save[t] = it[CP(i)].x[t];
        REP(t,48) it[CP(i)].x[t] = save[(t + it[i].rot) % 48];

        it[i].rot = 0;
    }
}

int get(int i, int l, int r, int u, int v) {
    if (l > r) return 0;
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].x[0];

    down(i, l, r);
    int mid = (l + r) >> 1;
    int res = get(CT(i), l, mid, u, v) + get(CP(i), mid+1, r, u, v);

    REP(t,48) it[i].x[t] = (it[CT(i)].x[t] + it[CP(i)].x[t]) % MOD;

    return res % MOD;
}

void update(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].rot++; if (it[i].rot == 48) it[i].rot = 0;

        REP(t,48) save[t] = it[i].x[t];
        REP(t,48) it[i].x[t] = save[(t + 1) % 48];
        return ;
    }
    down(i, l, r);

    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u, v);
    update(CP(i), mid+1, r, u, v);

    REP(t,48) it[i].x[t] = (it[CT(i)].x[t] + it[CP(i)].x[t]) % MOD;
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        build(1,1,n);

        int q; scanf("%d", &q);
        while (q--) {
            int t, u, v; scanf("%d%d%d", &t, &u, &v);
            if (t == 1) {
                printf("%d\n", get(1,1,n,u,v));
            }
            else {
                update(1,1,n,u,v);
            }
        }
    }
    return 0;
}