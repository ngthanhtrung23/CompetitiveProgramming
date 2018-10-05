
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

template<typename flow_t = long long>
struct PushRelabel {
    struct Edge {
        int to, rev;
        flow_t f, c;
    };
    vector<vector<Edge> > g;
    PushRelabel(int n) : g(n), ec(n), cur(n), hs(2*n), H(n) {}

    int addEdge(int s, int t, flow_t cap, flow_t rcap=0) {
        if (s == t) return -1;
        Edge a = {t, (int)g[t].size(), 0, cap};
        Edge b = {s, (int)g[s].size(), 0, rcap};
        g[s].push_back(a);
        g[t].push_back(b);

        // Return ID of forward edge.
        return b.rev;
    }

    flow_t maxFlow(int s, int t) {
        int v = g.size();
        H[s] = v;
        ec[t] = 1;
        vector<int> co(2*v);
        co[0] = v-1;
        for (int i = 0; i < v; ++i) {
            cur[i] = g[i].data();
        }
        for (auto &e : g[s]) {
            add_flow(e, e.c);
        }
        if (hs[0].size()) {
            for (int hi = 0; hi >= 0;) {
                int u = hs[hi].back();
                hs[hi].pop_back();
                while (ec[u] > 0) { // discharge u
                    if (cur[u] == g[u].data() + g[u].size()) {
                        H[u] = 1e9;
                        for (auto &e : g[u]) {
                            if (e.c && H[u] > H[e.to]+1) {
                                H[u] = H[e.to]+1;
                                cur[u] = &e;
                            }
                        }
                        if (++co[H[u]], !--co[hi] && hi < v) {
                            for (int i = 0; i < v; ++i) {
                                if (hi < H[i] && H[i] < v){
                                    --co[H[i]];
                                    H[i] = v + 1;
                                }
                            }
                        }
                        hi = H[u];
                    } else if (cur[u]->c && H[u] == H[cur[u]->to] + 1) {
                        add_flow(*cur[u], min(ec[u], cur[u]->c));
                    }
                    else {
                        ++cur[u];
                    }
                }
                while (hi>=0 && hs[hi].empty()) --hi;
            }
        }
        return -ec[s];
    }

private:
    vector<flow_t> ec;
    vector<Edge*> cur;
    vector<vector<int> > hs;
    vector<int> H;

    void add_flow(Edge& e, flow_t f) {
        Edge &back = g[e.to][e.rev];
        if (!ec[e.to] && f) {
            hs[H[e.to]].push_back(e.to);
        }
        e.f += f; e.c -= f;
        ec[e.to] += f;
        back.f -= f; back.c += f;
        ec[back.to] -= f;
    }
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
    int from;
    int eid;
};

E forwardEdges[200111];

int32_t main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout << (fixed) << setprecision(9) << boolalpha;
    int n, m;
    GN(n); GN(m);
    PushRelabel<int> flow(n);
    REP(i,m) {
        int u, v, f;
        GN(u); GN(v); GN(f);

        forwardEdges[i].from = u - 1;
        forwardEdges[i].eid = flow.addEdge(u-1, v-1, f, f);
    }

    int res = flow.maxFlow(0, n-1);
    // DEBUG(res);

    REP(i,m) {
        int u = forwardEdges[i].from;
        int eid = forwardEdges[i].eid;

        if (flow.g[u][eid].f >= 0) puts("0");
        else puts("1");
    }

    return 0;
}
