
#include "bits/stdc++.h"
using namespace std;

#define int long long
#define FOR(i, a, b) for (int i = (a), _##i = (b); i <= _##i; ++i)
#define FORD(i, a, b) for (int i = (a), _##i = (b); i >= _##i; --i)
#define REP(i, a) for (int i = 0, _##i = (a); i < _##i; ++i)
#define REPD(i,n) for(int i = (n)-1; i >= 0; --i)

#define DEBUG(X) { auto _X = (X); cerr << "L" << __LINE__ << ": " << #X << " = " << (_X) << endl; }
#define PR(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; FOR(_, 1, n) cerr << A[_] << ' '; cerr << endl; }
#define PR0(A, n) { cerr << "L" << __LINE__ << ": " << #A << " = "; REP(_, n) cerr << A[_] << ' '; cerr << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
// On CF, GNU C++ seems to have some precision issues with long double?
// #define double long double
typedef pair<int, int> II;
#define __builtin_popcount __builtin_popcountll
#define SZ(x) ((int)(x).size())
#define ALL(a) (a).begin(), (a).end()
#define MS(a,x) memset(a, x, sizeof(a))
#define next ackjalscjaowjico
#define prev ajcsoua0wucckjsl
#define y1 alkscj9u20cjeijc
#define left lajcljascjljl
#define right aucouasocjolkjl
#define y0 u9cqu3jioajc

#define TWO(X) (1LL<<(X))
#define CONTAIN(S,X) (((S) >> (X)) & 1)

long long rand16() {
    return rand() & (TWO(16) - 1);
}
long long my_rand() {
    return rand16() << 32 | rand16() << 16 | rand16();
}

double safe_sqrt(double x) { return sqrt(max((double)0.0, x)); }
int GI(long long& x) { return scanf("%lld", &x); }

template<typename flow_t = int, typename excess_t = long long>
struct Flow{
    struct Edge{
        int to, next; flow_t f;
        void set(int _to, flow_t _f, int _n){
            tie(to, next, f)=make_tuple(_to, _n, _f);
        }
    };
    int n, ledge, s, t, *fe, *h, *hp, *cnt, htop;
    Edge* ed;
    excess_t *ex, flow;
    bool *isq;
    int add_edge(int a, int b, flow_t cap, flow_t rcap = flow_t(0)){
        assert(a>0&&b>0&&a<n&&b<n);
        if(a==b) return -1;
        ed[ledge].set(a, rcap, fe[b]);
        fe[b] = ledge++;
        ed[ledge].set(b, cap, fe[a]);
        fe[a] = ledge++;
        
        return ledge-1;
    }
    void push(int u, int v, int p) {
        flow_t d = ex[u] < ed[p].f ? ex[u] : ed[p].f;
        ed[p].f -= d, ed[p^1].f += d;
        ex[u] -= d, ex[v] += d;
    }
    inline void relabel(int u) {
        if(--cnt[h[u]]){
            int min_h = 2*n;
            for (int p = fe[u]; p; p = ed[p].next)
                if (ed[p].f > 0 && min_h > h[ed[p].to])
                    min_h = h[ed[p].to];
            ++cnt[h[u] = min_h + 1];
        } else {//gap
            for(int i=1;i<n;++i){
                if(i!=s && h[i]>h[u]){
                    --cnt[h[i]];
                    ++cnt[h[i]=h[s]+1];
                }
            }
            ++cnt[h[u]=h[s]+1];
        }
    }
    void hpush(int u) {
        int i;
        for (i = ++htop; h[hp[i >> 1]] < h[u]; i >>= 1)
            hp[i] = hp[i >> 1];
        hp[i] = u;
    }
    void hpop() {
        int last = hp[htop--], i, ch;
        for (i = 1; (i << 1) <= htop; i = ch) {
            ch = i << 1;
            if (ch != htop && h[hp[ch]] < h[hp[ch + 1]]) ++ch;
            if (h[last] >= h[hp[ch]]) break;
            else  hp[i] = hp[ch];
        }
        hp[i] = last;
    }
    inline void init() {
        fill(h, h + n, n+2);
        fill(cnt, cnt + 2*n + 2, 0);
        h[hp[0]=0] = ~0u >> 1;
        int f = 1, b = 1;
        cnt[h[s] = n+1] = cnt[h[t] = 0] = 1;
        hp[b++] = t;
        while (f < b) {
            int u = hp[f++];
            for (int p = fe[u]; p; p = ed[p].next) {
                int v = ed[p].to;
                if (h[v] == n+2 && ed[p^1].f > 0) {
                    ++cnt[h[v] = h[u] + 1];
                    hp[b++] = v;
                }
            }
        }
        flow = htop = 0;
        fill(ex, ex + n, 0);
        fill(isq, isq + n, 0);
        ex[s] = ~0llU >> 1;
        for (int p = fe[s]; p != 0; p = ed[p].next) {
            if (ed[p].f > 0) {
                int v = ed[p].to;
                push(s, v, p);
                if(!isq[v]) {
                    hpush(v);
                    isq[v] = true;
                }
            }
        }
    }
    excess_t max_flow() {
        init();
        while (htop) {
            int u = hp[1];
            if (u == t) {
                hpop();
            } else {
                for (int p = fe[u]; p; p = ed[p].next) {
                    int v = ed[p].to;
                    if (ed[p].f > 0 && h[u] == h[v] + 1) {
                        push(u, v, p);
                        if (isq[v] == false) {
                            if (v != s && v != t)
                                hpush(v);
                            isq[v] = true;
                        }
                        if (ex[u] == 0) {
                            hpop();
                            isq[u] = false;
                            break;
                        }
                    }
                }
                if (ex[u]) relabel(u);
            }
        }
        return ex[t];
    }
    Flow(int N, int M, int S, int T):n(N+1), ledge(2), s(S), t(T), fe(new int[n]), h(new int[n]), hp(new int[n+2]), cnt(new int[2*n+2]), htop(0), ed(new Edge[2*M+2]), ex(new excess_t[n]), isq(new bool[n]){fill(fe, fe+n, 0);}
    Flow(int N, int M):Flow(N+2, M, N+1, N+2){}
    ~Flow(){delete[] fe, delete[]h, delete[]hp, delete[]cnt, delete[]ed, delete[]ex; delete[]isq;}
};

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

struct E {
    int eid;
    int cap;
};

E forwardEdges[200111];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int n, m;
    GN(n); GN(m);
    Flow<int,int> flow(n, m, 1, n);
    REP(i,m) {
        int u, v, f;
        GN(u); GN(v); GN(f);

        forwardEdges[i].eid = flow.add_edge(u, v, f, f);
        forwardEdges[i].cap = f;
    }

    int res = flow.max_flow();
    DEBUG(res);

    REP(i,m) {
        int eid = forwardEdges[i].eid;

        if (flow.ed[eid].f <= forwardEdges[i].cap) puts("0");
        else puts("1");
    }

    return 0;
}
