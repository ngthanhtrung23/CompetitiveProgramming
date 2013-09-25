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

struct City {
    vector< pair< pair<int,int>, int > > ke;
} a[MN];
int n, d[MN], old[MN];

set< pair<int,int> > s;
string tmp;

int next() {
    int h, m; scanf("%d:%d", &h, &m);
    return h * 60 + m;
}

inline void print(int x) {
    int h = x / 60, m = x % 60;
    if (h < 10) putchar('0'); printf("%d:", h);
    if (m < 10) putchar('0'); printf("%d", m);
}

int c[MN*10];

vector< pair<int,int> > res;

void dijkstra() {
    while (!s.empty()) {
        int u = s.begin()->second, l = s.begin()->first;
        s.erase(s.begin());

        if (l != d[u]) continue;

        __typeof(a[u].ke.begin()) it = lower_bound(a[u].ke.begin(), a[u].ke.end(), make_pair(make_pair(l, 0), 0));

        for(; it != a[u].ke.end(); ++it) {
            if (it->first.first >= old[u]) break;

            // cout << it->first.first << ' ' << it->first.second << ' ' << it->second << endl;

            int v = it->second;
            int l2 = it->first.second;
            if (l2 < d[v]) {
                d[v] = l2;
                s.insert(make_pair(l2, v));
            }
        }
        old[u] = l;
    }
}

int main() {
    scanf("%d", &n);
    FOR(i,1,n) d[i] = old[i] = 1000111000;

    FOR(i,1,n) {
        int k; scanf("%d", &k);
        a[i].ke.resize(k);
        REP(t,k) {
            a[i].ke[t].first.first = next();
            a[i].ke[t].first.second = next();
            scanf("%d", &a[i].ke[t].second);
        }
    }

    s.clear();
    int sc = 0;
    REP(t,a[1].ke.size()) {
        c[++sc] = a[1].ke[t].first.first;
    }
    sort(c+1, c+sc+1);
    sc = unique(c+1, c+sc+1) - c - 1;

    res.clear();

    FORD(t,sc,1) {
        int cur = d[n];

        s.clear();
        d[1] = c[t];
        s.insert(make_pair(d[1], 1));
        dijkstra();

        if (d[n] < cur) {
            res.push_back(make_pair(c[t], d[n]));
        }
        // PR(d, n);
    }
    cout << res.size() << endl;
    FORD(i,res.size()-1,0) {
        print(res[i].first); putchar(' ');
        print(res[i].second); puts("");
    }
    return 0;
}
