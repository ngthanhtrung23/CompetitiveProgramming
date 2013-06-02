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

struct Node {
    vector<long long> sum[11];
} it[100111 * 3];

int n, a[100111];

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

inline void cal(int i) {
    for(int t = 2; t <= 10; t += 2) {
        for(int x = 0; x < t; ++x)
            it[i].sum[t][x] = it[CT(i)].sum[t][x] + it[CP(i)].sum[t][x];
    }
}

void build(int i, int l, int r) {
    for(int t = 2; t <= 10; t += 2)
        it[i].sum[t].resize(t);
    if (l == r) {
        for(int t = 2; t <= 10; t += 2) {
            REP(x,t) it[i].sum[t][x] = 0;
            it[i].sum[t][l % t] += a[l];
        }
        return ;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);

    cal(i);
}

void update(int i, int l, int r, int p, int v) {
    if (p < l || p > r) return ;
    if (l == r) {
        for(int t = 2; t <= 10; t += 2) {
            it[i].sum[t][l % t] = v;
        }
        return ;
    }

    int mid = (l + r) >> 1;
    update(CT(i), l, mid, p, v);
    update(CP(i), mid+1, r, p, v);

    cal(i);
}

long long get(int i, int l, int r, int u, int v, int t, int x) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].sum[t][x];

    int mid = (l + r) >> 1;
    return get(CT(i), l, mid, u, v, t, x) + get(CP(i), mid+1, r, u, v, t, x);
}

int main() {
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d", &a[i]);
        build(1, 1, n);
        int q; scanf("%d", &q);
        while (q--) {
            int req; scanf("%d", &req);
            if (req == 1) {
                int p, v; scanf("%d%d", &p, &v);
                update(1, 1, n, p, v);
            }
            else {
                int l, r, z; scanf("%d%d%d", &l, &r, &z);
                long long res = 0;
                int mod = 2 * (z - 1);
                FOR(i,1,z) {
                    res += i * get(1, 1, n, l, r, mod, (l+i-1) % mod);
                    // cout << mod << ' ' << (l+i-1) % mod << ' ' << i << ' ' << get(1, 1, n, l, r, mod, (l+i-1) % mod) << endl;
                    // DEBUG(res);
                }
                FORD(i,z-1,2) {
                    res += i * get(1, 1, n, l, r, mod, (l+z + z-1-i) % mod);
                    // cout << mod << ' ' << (l+z + z-1-i) % mod << ' ' << i << ' ' << get(1, 1, n, l, r, mod, (l+z + z-1-i) % mod) << endl;
                    // DEBUG(res);
                }
                cout << res << endl;
            }
        }
    }
    return 0;
}
