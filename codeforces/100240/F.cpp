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

const int MN = 10111;
const int oo = 1000111000;

int price[MN];
vector< pair<int,int> > ke[MN];
int d[MN][111], cap;
set< pair<int, pair<int,int> > > s;
int n, m;

bool cmp(const pair<int,int> &x, const pair<int,int> &y) {
    return x.second < y.second;
}

int main() {
    ios :: sync_with_stdio(false);
    while (cin >> n >> m) {
        FOR(i,1,n) {
            cin >> price[i];
            ke[i].clear();
        }
        FOR(i,1,m) {
            int u, v, c; cin >> u >> v >> c;
            ++u; ++v;
            ke[u].push_back(make_pair(v, c));
            ke[v].push_back(make_pair(u, c));
        }
        FOR(i,1,n) {
            sort(ke[i].begin(), ke[i].end(), cmp);
        }
        int q; cin >> q;
        while (q--) {
            int start, target; cin >> cap >> start >> target;
            ++start; ++target;

            FOR(u,1,n) FOR(x,0,cap) d[u][x] = oo;

            s.clear();
            FOR(x,0,cap) {
                d[start][x] = price[start] * x;
                s.insert(make_pair(d[start][x], make_pair(start, x)));
            }

            bool ok = false;
            while (!s.empty()) {
                int l = s.begin()->first;
                int u = s.begin()->second.first, x = s.begin()->second.second;
                s.erase(s.begin());

                if (u == target) {
                    cout << l << endl;
                    ok = true;
                    break;
                }

                if (l != d[u][x]) continue;
                if (x + 1 <= cap) {
                    int now = l + price[u];
                    if (now < d[u][x+1]) {
                        d[u][x+1] = now;
                        s.insert(make_pair(now, make_pair(u, x+1)));
                    }
                }

                REP(i,ke[u].size()) {
                    int v = ke[u][i].first, c = ke[u][i].second;
                    if (c > x) break;
                    if (d[v][x-c] > l) {
                        d[v][x-c] = l;
                        s.insert(make_pair(l, make_pair(v, x - c)));
                    }
                }
            }
            if (!ok) cout << "impossible\n";
        }
    }
    return 0;
}
