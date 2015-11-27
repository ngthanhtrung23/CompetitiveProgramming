
#include <bits/stdc++.h>
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << X << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 30111;
const ll MOD = 1e9 + 7;
const ll P = 1e7 + 19;

struct Obj {
    int w, v, from, to;
} a[MN];

int res[MN];
ll f[22][MN], p[MN];

vector<int> it[MN * 4];

int nQuery, nObj, k;

void init(int i, int l, int r) {
    it[i].clear();
    if (l == r) return ;
    int mid = (l + r) >> 1;
    init(i<<1, l, mid);
    init(i<<1|1, mid+1, r);
}

void add(int i, int l, int r, int x, int u, int v) {
    if (v < l || r < u) return ;
    if (u <= l && r <= v) {
        it[i].push_back(x);
        return ;
    }
    int mid = (l + r) >> 1;
    add(i<<1, l, mid, x, u, v);
    add(i<<1|1, mid+1, r, x, u, v);
}

void go(int i, int l, int r, int h) {
    // init from parent
    FOR(i,0,k) f[h][i] = f[h-1][i];
    // add all the objects of this node
    for(int x : it[i]) {
        int w = a[x].w;
        int v = a[x].v;

        FORD(sumw,k,w)
            f[h][sumw] = max(f[h][sumw], f[h][sumw - w] + v);
    }
    // if leaf node, need to answer
    if (l == r) {
        res[l] = 0;
        FOR(m,1,k)
            res[l] = (res[l] + f[h][m] * p[m-1]) % MOD;
        return ;
    }
    int mid = (l + r) >> 1;
    go(i<<1, l, mid, h+1);
    go(i<<1|1, mid+1, r, h+1);
}

int main() {
    int n, q;
    p[0] = 1;
    FOR(i,1,MN-1) p[i] = p[i-1] * P % MOD;

    while (scanf("%d%d", &n, &k) == 2) {
        nObj = 0;
        FOR(i,1,n) {
            int v, w;
            scanf("%d%d", &v, &w);
            ++nObj;
            a[nObj].w = w;
            a[nObj].v = v;
            a[nObj].from = 1;
            a[nObj].to = -1;
        }
        nQuery = 0;
        scanf("%d", &q);
        FOR(i,1,q) {
            int typ;
            scanf("%d", &typ);
            if (typ == 1) {
                ++nObj;
                scanf("%d%d", &a[nObj].v, &a[nObj].w);
                a[nObj].from = nQuery + 1;
                a[nObj].to = -1;
            }
            else if (typ == 2) {
                int x; scanf("%d", &x);
                a[x].to = nQuery;
            }
            else { // typ == 3
                ++nQuery;
            }
        }
        FOR(i,1,nObj) if (a[i].to < 0) a[i].to = nQuery;

        init(1, 1, nQuery);
        FOR(i,1,nObj) {
            add(1, 1, nQuery, i, a[i].from, a[i].to);
        }

//        FOR(i,1,nObj) {
//            cout << i << ": " << a[i].from << ' ' << a[i].to << ": " << a[i].w << ' ' << a[i].v << endl;
//        }

        go(1, 1, nQuery, 1);

        FOR(i,1,nQuery) printf("%d\n", (int) res[i]);
        puts("");
    }
}
