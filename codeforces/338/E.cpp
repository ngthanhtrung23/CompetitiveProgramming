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

const int MN = 150111;
const int oo = 1000111000;

int len, n, a[MN], b[MN], h, need[MN], id[MN], has[MN];
pair<int,int> c[MN];

struct Node {
    int min, add, cnt;
} it[MN * 6];

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

inline void update(int i) {
    it[i].min = min(it[CT(i)].min, it[CP(i)].min);
    it[i].cnt = it[CT(i)].cnt + it[CP(i)].cnt;
}

inline void down(int i) {
    if (it[i].add) {
        it[CT(i)].add += it[i].add;
        it[CT(i)].min += it[i].add;

        it[CP(i)].add += it[i].add;
        it[CP(i)].min += it[i].add;

        it[i].add = 0;
    }
}

void build(int i, int l, int r) {
    if (l == r) {
        it[i].min = has[l];
        it[i].add = 0;
        if (it[i].min != oo) it[i].cnt = 1;
        else it[i].cnt = 0;

        // cout << i << ' ' << l << ' ' << r << "   " << it[i].min << endl;

        return ;
    }
    int mid = (l + r) >> 1;

    build(CT(i), l, mid);
    build(CP(i), mid+1, r);

    update(i);
    it[i].add = 0;

    // cout << i << ' ' << l << ' ' << r << "   " << it[i].min << endl;
}

void init() {
    FOR(i,1,len) {
        c[i] = make_pair(a[i], i);
    }
    sort(c+1, c+len+1);

    FOR(i,1,n) has[i] = oo;

    FOR(i,1,len) {
        int x = c[i].second;
        has[id[x]] = (len - i + 1) - need[x];
    }

    // PR(has, n);

    build(1, 1, n);
}

void remove(int i, int l, int r, int x) {
    if (x < l || r < x) return ;
    if (l == r) {
        it[i].min = oo;
        it[i].cnt = 0;
        it[i].add = 0;

        return ;
    }

    down(i);

    int mid = (l + r) >> 1;
    remove(CT(i), l, mid, x);
    remove(CP(i), mid+1, r, x);

    update(i);
}

void add(int i, int l, int r, int x, int val) {
    if (x < l || r < x) return ;
    if (l == r) {
        it[i].min = val;
        it[i].add = 0;
        it[i].cnt = 1;

        return ;
    }

    down(i);

    int mid = (l + r) >> 1;
    add(CT(i), l, mid, x, val);
    add(CP(i), mid+1, r, x, val);

    update(i);
}

int get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return 0;
    if (u <= l && r <= v) return it[i].cnt;

    int mid = (l + r) >> 1;
    return get(CT(i), l, mid, u, v) + get(CP(i), mid+1, r, u, v);
}

void updateVal(int i, int l, int r, int u, int v, int k) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].min += k;
        it[i].add += k;
        return ;
    }

    down(i);

    int mid = (l + r) >> 1;
    updateVal(CT(i), l, mid, u, v, k);
    updateVal(CP(i), mid+1, r, u, v, k);

    update(i);
}

void solve() {
    int res = 0;
    if (it[1].min >= 0) ++res;

    // PR(need, n);

    FOR(last,len+1,n) {
        int x = id[last - len];

        remove(1, 1, n, x);
        updateVal(1, 1, n, x+1, n, 1);

        // cout << "Remove " << x << endl;
        // DEBUG(it[1].min);

        x = id[last];

        int cnt = get(1, 1, n, 1, x-1);
        int val = (len - cnt) - need[last];

        add(1, 1, n, x, val);
        updateVal(1, 1, n, x+1, n, -1);

        // cout << "Add " << x << endl;
        // DEBUG(it[1].min);

        if (it[1].min >= 0) ++res;
    }

    cout << res << endl;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> len >> h) {
        FOR(i,1,len) cin >> b[i];
        FOR(i,1,n) {
            cin >> a[i];
            c[i] = make_pair(a[i], i);
        }
        sort(c+1, c+n+1);
        FOR(i,1,n)
            id[c[i].second] = i;

        sort(b+1, b+len+1);
        FOR(i,1,n) {
            if (a[i] + b[len] < h) need[i] = oo;
            else need[i] = lower_bound(b+1, b+len+1, h - a[i]) - b;
        }

        init();
        solve();
    }
    return 0;
}
