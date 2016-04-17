#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int) (x).size())
using namespace std;

int INP,AM,REACHEOF;
#define BUFSIZE (1<<12)
char BUF[BUFSIZE+1], *inp=BUF;
#define GETCHAR(INP) { \
    if(!*inp && !REACHEOF) { \
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

const int MN = 200111;
int it[MN * 4];

int get(int i, int l, int r, int u) {
    if (l == r) return it[i];
    int mid = (l + r) >> 1;
    int res = it[i];

    if (u <= mid) res += get(i<<1, l, mid, u);
    else res += get(i<<1|1, mid+1, r, u);

    return res;
}
void update(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i]++;
        return ;
    }
    int mid = (l + r) >> 1;
    update(i<<1, l, mid, u, v);
    update(i<<1|1, mid+1, r, u, v);
}

int ql[MN], qr[MN], qres[MN], qmid[MN];
int n, a[MN], b[MN];

vector<int> queriesAt[MN];

int main() {
    ios :: sync_with_stdio(0); cin.tie(0);
    cout << (fixed) << setprecision(9);
    GN(n);
    FOR(i,1,n) {
        GN(a[i]);
        GN(b[i]);

        ql[i] = 1, qr[i] = n; qres[i] = n+1;
    }
    REP(turn,20) {
        memset(it, 0, sizeof it);
        FOR(i,1,n) queriesAt[i].clear();

        int need = 0;
        FOR(i,1,n) {
            if (ql[i] > qr[i]) continue;
            need = 1;
            qmid[i] = (ql[i] + qr[i]) / 2;
            queriesAt[qmid[i]].push_back(i);
        }
        if (!need) break;

        FOR(i,1,n) {
            update(1, 1, n, a[i], b[i]);
            for(int x : queriesAt[i]) {
                int t = get(1, 1, n, x);
                if (t >= x) {
                    qres[x] = qmid[x];
                    qr[x] = qmid[x] - 1;
                }
                else {
                    ql[x] = qmid[x] + 1;
                }
            }
        }
    }
    FOR(i,1,n) if (qres[i] == n+1) qres[i] = -1;
    FOR(i,1,n) printf("%d ", qres[i]);
    puts("");
}
