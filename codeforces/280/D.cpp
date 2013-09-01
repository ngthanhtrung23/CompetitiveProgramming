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

const int MN = 100111;

template<typename T> T MIN(T a, T b) { return (a < b) ? a : b; }
template<typename T> T MAX(T a, T b) { return (a > b) ? a : b; }

struct Val {
    int u, v, val;

    Val(int u = 0, int v = 0, int val = 0) : u(u), v(v), val(val) {}

    Val operator + (Val a) {
        return Val(min(u, a.u), max(v, a.v), val + a.val);
    }

    bool operator < (const Val &a) { return val < a.val; }
    bool operator > (const Val &a) { return val > a.val; }

    void neg() { val = -val; }
};

struct Node {
    struct F {
        Val left, right, gss;
        void neg() { left.neg(); right.neg(); gss.neg(); }
    } nn, ln;

    bool neg;
    Val sum;

    void negate() {
        neg = !neg;
        nn.neg(); ln.neg();
        sum.neg();

        swap(nn, ln);
    }
} it[MN * 3];
int a[MN], n;

#define CT(x) ((x) << 1)
#define CP(x) (CT(x) + 1)

inline void update(int i) {
    it[i].sum = it[CT(i)].sum + it[CP(i)].sum;

    it[i].nn.left  = MIN(it[CT(i)].nn.left, it[CT(i)].sum + it[CP(i)].nn.left);
    it[i].nn.right = MIN(it[CP(i)].nn.right, it[CP(i)].sum + it[CT(i)].nn.right);
    it[i].nn.gss   = MIN(
            MIN(it[CT(i)].nn.gss, it[CP(i)].nn.gss),
            it[CT(i)].nn.right + it[CP(i)].nn.left
    );

    it[i].ln.left  = MAX(it[CT(i)].ln.left, it[CT(i)].sum + it[CP(i)].ln.left);
    it[i].ln.right = MAX(it[CP(i)].ln.right, it[CP(i)].sum + it[CT(i)].ln.right);
    it[i].ln.gss   = MAX(
            MAX(it[CT(i)].ln.gss, it[CP(i)].ln.gss),
            it[CT(i)].ln.right + it[CP(i)].ln.left
    );
}

inline void refine(int i) {
    if (it[i].neg) {
        it[CT(i)].negate();
        it[CP(i)].negate();
        it[i].neg = false;
    }
}

void build(int i, int l, int r) {
    it[i].neg = false;
    if (l == r) {
        it[i].nn.left = it[i].nn.right = it[i].nn.gss = Val(l, l, a[l]);
        it[i].ln.left = it[i].ln.right = it[i].ln.gss = Val(l, l, a[l]);
        it[i].sum = Val(l, l, a[l]);
        return ;
    }
    int mid = (l + r) >> 1;
    build(CT(i), l, mid);
    build(CP(i), mid+1, r);

    update(i);
}

void negateSeg(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].negate();
        return ;
    }
    refine(i);
    int mid = (l + r) >> 1;
    negateSeg(CT(i), l, mid, u, v);
    negateSeg(CP(i), mid+1, r, u, v);

    update(i);
}

int top = 0;
Node x[1011];

void get(int i, int l, int r, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        x[++top] = it[i];
        return ;
    }
    refine(i);
    int mid = (l + r) >> 1;
    get(CT(i), l, mid, u, v);
    get(CP(i), mid+1, r, u, v);
    update(i);
}

Val getMax(int u, int v) {
    top = 0;
    get(1, 1, n, u, v);

    Val res = Val(0, 0, 0), maxright = Val(0, 0, 0);

    FOR(i,1,top) {
        res = MAX(res, x[i].ln.gss);
        res = MAX(res, maxright + x[i].ln.left);

        maxright = MAX(x[i].ln.right, maxright + x[i].sum);
    }

    return res;
}

void modify(int i, int l, int r, int u, int val) {
    if (u < l || r < u) return ;
    if (l == r) {
        it[i].nn.left = it[i].nn.right = it[i].nn.gss = Val(l, l, val);
        it[i].ln.left = it[i].ln.right = it[i].ln.gss = Val(l, l, val);
        it[i].sum = Val(l, l, val);
        return ;
    }
    refine(i);
    int mid = (l + r) >> 1;
    modify(CT(i), l, mid, u, val);
    modify(CP(i), mid+1, r, u, val);
    update(i);
}

pair<int,int> save[22];

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        build(1,1,n);

        int q; cin >> q;
        while (q--) {
            int type; cin >> type;
            if (type == 0) {
                int u, val; cin >> u >> val;
                modify(1, 1, n, u, val);
            }
            else {
                int l, r, k; cin >> l >> r >> k;
                int res = 0;
                FOR(kk,1,k) {
                    Val cur = getMax(l, r);
                    if (cur.val > 0) {
                        res += cur.val;
                        save[kk] = make_pair(cur.u, cur.v);
                        negateSeg(1, 1, n, cur.u, cur.v);
                    }
                    else save[kk] = make_pair(-1, -1);
                }
                FOR(kk,1,k) {
                    if (save[kk].first != -1) {
                        negateSeg(1, 1, n, save[kk].first, save[kk].second);
                    }
                }
                cout << res << endl;
            }
        }
        cout << endl;
    }
    return 0;
}
