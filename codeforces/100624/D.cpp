#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define EACH(it,a) for(__typeof(a.begin()) it = a.begin(); it != a.end(); ++it)

#define DEBUG(x) { cout << #x << " = "; cout << (x) << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define next __next
#define prev __prev
using namespace std;

const int MN = 200111;

int n, a[MN], next[MN], prev[MN], c[MN], id[MN];

void RR() {
    FOR(i,1,n) c[i] = a[i];
    sort(c+1, c+n+1);
    FOR(i,1,n) a[i] = lower_bound(c+1, c+n+1, a[i]) - c;
}

void init() {
    FOR(i,1,n) {
        if (id[a[i]] < 0) prev[i] = 0;
        else prev[i] = id[a[i]];
        id[a[i]] = i;
    }
    FOR(i,1,n) id[a[i]] = -1;
    FORD(i,n,1) {
        if (id[a[i]] < 0) next[i] = n+1;
        else next[i] = id[a[i]];
        id[a[i]] = i;
    }
    FOR(i,1,n) id[a[i]] = -1;
}

pair<int,int> lefts[MN];
pair<int,int> it[MN * 4];

#define CT(X) ((X) << 1)
#define CP(X) (CT(X) + 1)
pair<int,int> get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return make_pair(0, 0);
    if (u <= l && r <= v) return it[i];

    int mid = (l + r) >> 1;
    auto x = get(CT(i), l, mid, u, v);
    auto y = get(CP(i), mid+1, r, u, v);
    if (x.first > y.first) return x;
    else return y;
}

void update(int i, int l, int r, int u) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i] = make_pair(next[u], u);
        return ;
    }
    int mid = (l + r) >> 1;
    update(CT(i), l, mid, u);
    update(CP(i), mid+1, r, u);

    if (it[CT(i)].first > it[CP(i)].first)
        it[i] = it[CT(i)];
    else it[i] = it[CP(i)];
}

int updated;
bool solve(int l, int r) {
    if (l >= r) return true;
    while (updated < n && lefts[updated+1].first < l) {
        ++updated;
        update(1, 1, n, lefts[updated].second);
    }

    auto p = get(1, 1, n, l, r);

    if (p.first <= r) return false;

    return solve(l, p.second - 1) && solve(p.second + 1, r);
}

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
int main() {
    int ntest = 0; GN(ntest);
    while (ntest--) {
        GN(n);
        FOR(i,1,n) GN(a[i]);
        RR();
//        PR(a, n);
        init();
//        PR(prev, n);
//        PR(next, n);

        FOR(i,1,n) lefts[i] = make_pair(prev[i], i);
        sort(lefts+1, lefts+n+1);
        updated = 0;
        FOR(i,1,4*n) it[i].first = 0;
        puts(solve(1, n) ? "non-boring" : "boring");
    }
    return 0;
}