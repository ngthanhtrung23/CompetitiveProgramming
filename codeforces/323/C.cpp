#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
int INP,AM,REACHEOF;
const int BUFSIZE = (1<<12) + 17;
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
//End of buffer reading

const int MN = 1000111;
const int oo = 1000111000;
int n, a[MN], inb[MN];
vector<int> it[MN * 4];

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

void build(int i, int l, int r) {
    it[i].clear();
    if (l == r) {
        it[i].push_back(inb[a[l]]);
        it[i].push_back(oo);
        return ;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);

    it[i].resize(r - l + 1);
    merge(it[CT(i)].begin(), it[CT(i)].end() - 1,
            it[CP(i)].begin(), it[CP(i)].end() - 1,
            it[i].begin());

    it[i].push_back(oo);
    // cout << i << ' ' << l << ' ' << r << endl;
    // PR0(it[i], it[i].size());
}

int get(int i, int l, int r, int u, int v, int x, int y) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) {
        return upper_bound(it[i].begin(), it[i].end(), y)
                - (lower_bound(it[i].begin(), it[i].end(), x));
    }
    int mid = (l + r) >> 1;
    return get(CT(i), l, mid, u, v, x, y) + get(CP(i), mid+1, r, u, v, x, y);
}

int x;
inline int f(int z) {
    return (z - 1 + x + n) % n + 1;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) cin >> x, inb[x] = i;

        build(1, 1, n);

        int q; cin >> q;
        x = 0;
        while (q--) {
            int a, b, c, d; cin >> a >> b >> c >> d;
            int l1 = f(a), r1 = f(b); if (l1 > r1) swap(l1, r1);
            int l2 = f(c), r2 = f(d); if (l2 > r2) swap(l2, r2);
            x = get(1, 1, n, l1, r1, l2, r2);
            printf("%d\n", x);
            ++x;
        }
    }
    return 0;
}
