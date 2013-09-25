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

struct State {
    vector< pair<int,int> > x;

    void init() {
        sort(x.begin(), x.end());
    }

    int hash() {
        int res = 0;
        REP(i,4) {
            res = res * 10 + x[i].first;
            res = res * 10 + x[i].second;
        }
        return res;
    }

    void read() {
        x.resize(4);
        REP(i,4) cin >> x[i].first >> x[i].second;
        init();
    }

    void print() {
        REP(i,4) cout << x[i].first << ' ' << x[i].second << "   ";
        cout << endl;
    }
} start, target;

bool operator < (const State &a, const State &b) {
    return a.x < b.x;
}

bool operator == (const State &a, const State &b) {
    return a.x == b.x;
}

map< int, int > m;
pair< int, int > qu[11000111];
int first, last;

const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};

int has[111];

inline State decode(int x) {
    State res;
    res.x.resize(4);
    for(int i = 3; i >= 0; --i) {
        res.x[i].second = x % 10; x /= 10;
        res.x[i].first  = x % 10; x /= 10;
    }
    return res;
}

int main() {
    ios :: sync_with_stdio(false);
    start.read(); target.read();

    int first = last = 1;
    qu[1] = make_pair(start.hash(), 0);
    m[start.hash()] = 0;

    while (first <= last) {
        State cur = decode(qu[first].first);
        int l = qu[first].second;
        ++first;

        if (cur == target) {
            puts("YES");
            return 0;
        }

        if (l == 8) continue;

        REP(i,4) has[cur.x[i].first*10 + cur.x[i].second] = true;

        REP(u,4) REP(dir,4) {
            State next = cur;
            pair<int,int> from = cur.x[u];
            pair<int,int> to = make_pair(from.first + di[dir], from.second + dj[dir]);

            if (has[to.first*10 + to.second]) {
                to = make_pair(to.first + di[dir], to.second + dj[dir]);
            }
            if (has[to.first*10 + to.second]) continue;

            if (to.first > 0 && to.first < 9 && to.second > 0 && to.second < 9) {
                next.x[u] = to;
                next.init();

                int t = next.hash();

                if (m.find(t) == m.end()) {
                    m[t] = l + 1;
                    qu[++last] = make_pair(t, l+1);
                }
            }
        }

        REP(i,4) has[cur.x[i].first*10 + cur.x[i].second] = false;
    }
    puts("NO");
    return 0;
}
