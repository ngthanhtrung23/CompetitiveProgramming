#include <bits/stdc++.h>
#define int long long
#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; ++i)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; --i)
#define REP(i,a) for(int i=0,_a=(a); i < _a; ++i)

#define DEBUG(X) { cout << #X << " = " << (X) << endl; }
#define PR(A,n)  { cout << #A << " = "; FOR(_,1,n) cout << A[_] << ' '; cout << endl; }
#define PR0(A,n) { cout << #A << " = "; REP(_,n) cout << A[_] << ' '; cout << endl; }

#define sqr(x) ((x) * (x))
#define ll long long
#define SZ(x) ((int) (x).size())
using namespace std;

const int MN = 100111;
const int INF = 1000111000111000111LL;

int f[11][MN], it[MN * 2];
int n, q, p;
int a[MN], c[MN], nc;
int queries[MN];

int get(int l, int r) {
    if (l > r) return 0;
    --l;
    int res = 0;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
        if (l&1) res += it[l++];
        if (r&1) res += it[--r];

        if (res > INF) res = INF;
    }
    return res;
}

void update(int p, int value) {
    --p;
    p += n;
    it[p] += value; if (it[p] > INF) it[p] = INF;

    for (; p > 1; p >>= 1) {
        it[p>>1] = it[p] + it[p^1];
        if (it[p>>1] > INF) it[p>>1] = INF;
    }
}

void init() {
    FOR(len,1,p) {
        if (len == 1) {
            FORD(i,n,1) f[len][i] = 1;
        }
        else {
            memset(it, 0, sizeof it);
            FORD(i,n,1) {
                f[len][i] = get(1, a[i] - 1);
                update(a[i], f[len-1][i]);
            }
        }
//        PR(f[len], n);
    }
}

vector<int> queryAt[11][MN];
pair<int,int> order[MN];
vector<int> res[MN];

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


#undef int
int main() {
#define int long long
    ios :: sync_with_stdio(0); cin.tie(0);
    GN(n); GN(p); GN(q);
    FOR(i,1,n) GN(a[i]);
    FOR(i,1,n) c[i] = a[i];
    sort(c+1, c+n+1);
    nc = unique(c+1, c+n+1) - c - 1;
    FOR(i,1,n) a[i] = lower_bound(c+1, c+nc+1, a[i]) - c;

    init();

    FOR(i,1,q) GN(queries[i]);

    FOR(i,1,n) order[i] = make_pair(a[i], i);
    sort(order+1, order+n+1);

    int all = 0;
    FOR(i,1,n) {
        all += f[p][i];
        if (all > INF) all = INF;
    }

    FOR(len,1,p) {
        // find the len-th element of all queries
        if (len == 1) {
            // first element
            // add all the f[len][i] to it
            memset(it, 0, sizeof it);
            FOR(i,1,n) {
                update(i, f[p][i]);
            }

            FOR(i,1,q) if (queries[i] <= all) {
                int l = 1, r = n, result = n;
                while (l <= r) {
                    int mid = (l + r) >> 1;
                    if (get(1, mid) >= queries[i]) {
                        result = mid;
                        r = mid - 1;
                    }
                    else l = mid + 1;
                }
                res[i].clear();
                res[i].push_back(result);

                queries[i] -= get(1, result - 1);
                queryAt[1][result].push_back(i);
            }
        }
        else {
//                PR(queries, q);
            memset(it, 0, sizeof it);
            FOR(o,1,n) {
                int pos = order[o].second;
                // answer queries at pos
                for(auto i : queryAt[len-1][pos]) {
                    int l = pos+1, r = n, result = n;
                    while (l <= r) {
                        int mid = (l + r) >> 1;
                        if (get(pos+1, mid) >= queries[i]) {
                            result = mid;
                            r = mid - 1;
                        }
                        else l = mid + 1;
                    }
                    res[i].push_back(result);
                    queries[i] -= get(pos+1, result - 1);
                    queryAt[len][result].push_back(i);
                }
                // update
                update(pos, f[p - len + 1][pos]);
            }
        }
    }
    FOR(i,1,q) {
        if (queries[i] > all) puts("-1");
        else {
            for(int x : res[i]) {
                printf("%lld ", x);
            }
            puts("");
        }
    }
}
