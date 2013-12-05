#include <bits/stdc++.h>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)

#define DEBUG(x) { cout << #x << " = "; cout << x << endl; }
#define PR(a,n) { cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl; }
#define PR0(a,n) { cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl; }
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

int n;
long double p;
map< long long, long double> f;

#define TWO(x) (1<<(x))
#define CONTAIN(S,x) (S & TWO(x))
;

long long hash(vector<int> &x) {
    long long res = 0;
    REP(i,x.size()) {
        res = res * 1000007 + x[i];
    }
    return res;
}

long double get(vector<int> &cur) {
    if (cur.size() == 1) return 1.0;

    long long t = hash(cur);
    if (f.find(t) != f.end()) return f[t];

    long double res = 0.0;
    int k = cur[cur.size()-1];

    long double save[cur.size()];
    REP(i,cur.size()) save[i] = -1;
    memset(save, -1, sizeof save);

    REP(mask,TWO(cur.size()-1)) if (mask) {
        int nbit = __builtin_popcount(mask);
        if (save[nbit] > -0.5) {
            res += save[nbit];
            continue;
        }

        vector<int> next;
        int sz = cur.size()-1;
        int good = 0;
        long double prob = 1.0;

        REP(x,sz)
        if (CONTAIN(mask,x)) {
            good += cur[x];
            if (cur[x] > 1) puts(":@)");
            prob *= 1 - pow(1 - p, cur[x] * cur[sz]);
        }
        else {
            next.push_back(cur[x]);
            prob *= pow(1 - p, cur[x] * cur[sz]);
        }
        next.push_back(good);

        sort(next.begin(), next.end());
        save[nbit] = get(next) * prob;
        res += save[nbit];
    }
    // PR0(cur, cur.size()); DEBUG(res);
    return f[t] = res;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> p) {
        f.clear();
        vector<int> v;
        REP(i,n) v.push_back(1);
        cout << (fixed) << setprecision(11) << get(v) << endl;
    }
    return 0;
}
