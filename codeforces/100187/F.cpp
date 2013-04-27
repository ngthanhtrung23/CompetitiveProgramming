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

int nPeople, nVault, k, t;
int people[MN], vault[MN];
int sum[MN], first[MN * 3];

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void build(int i, int l, int r) {
    first[i] = l;
    if (l == r) return ;
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);
}

void update(int i, int l, int r, int u) {
    if (u < l || r < u) return ;
    if (l == r) {
        ++sum[l];
        if (sum[l] == k) first[i] = -1;
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u);
    update(CP(i), mid+1, r, u);

    first[i] = first[CT(i)];
    if (first[i] < 0) first[i] = first[CP(i)];
}

int check(int i, int l, int r, int u, int v) {
    if (v < vault[l] || u > vault[r]) return 0;

    if (u <= vault[l] && vault[r] <= v) {
        int id = first[i];
        if (id < 0) return 0;
        update(1, 1, nVault, id);
        return 1;
    }

    int mid = (l + r) >> 1;
    if (check(CT(i), l, mid, u, v)) return 1;
    return check(CP(i), mid+1, r, u, v);
}

int main() {
    while (scanf("%d%d%d%d", &nPeople, &nVault, &k, &t) == 4) {
        FOR(i,1,nPeople) scanf("%d", &people[i]);
        FOR(i,1,nVault) scanf("%d", &vault[i]);
        sort(people+1, people+nPeople+1);
        sort(vault+1, vault+nVault+1);

        memset(sum, 0, sizeof sum);
        build(1, 1, nVault);

        int res = 0;
        FOR(i,1,nPeople) {
            res += check(1, 1, nVault, people[i] - t, people[i] + t);
        }
        printf("%d\n", res);
    }
    return 0;
}
