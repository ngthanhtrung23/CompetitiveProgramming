#include <sstream>
#include <iomanip>
#include <iostream>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cmath>
#include <algorithm>
#include <vector>
#include <set>
#include <map>
#include <stack>
#include <queue>
#include <string>
#include <deque>
#include <complex>

#define FOR(i,a,b) for(int i=(a),_b=(b); i<=_b; i++)
#define FORD(i,a,b) for(int i=(a),_b=(b); i>=_b; i--)
#define REP(i,a) for(int i=0,_a=(a); i<_a; i++)
#define FORN(i,a,b) for(int i=(a),_b=(b);i<_b;i++)
#define DOWN(i,a,b) for(int i=a,_b=(b);i>=_b;i--)
#define SET(a,v) memset(a,v,sizeof(a))
#define sqr(x) ((x)*(x))
#define ll long long
#define F first
#define S second
#define PB push_back
#define MP make_pair

#define DEBUG(x) cout << #x << " = "; cout << x << endl;
#define PR(a,n) cout << #a << " = "; FOR(_,1,n) cout << a[_] << ' '; cout << endl;
#define PR0(a,n) cout << #a << " = "; REP(_,n) cout << a[_] << ' '; cout << endl;
using namespace std;

//Buffer reading
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
//End of buffer reading

const long double PI = acos((long double) -1.0);

struct Work {
    int s, p, t;
} a[50111];

bool operator < (const Work &a, const Work &b) {
    if (a.t != b.t) return a.t < b.t;
    if (a.s != b.s) return a.s < b.s;
    return a.p < b.p;
}

int n, values[100111], p[50111], nValue, id, progress[50111];
long long finish[50111], T;

void add(int v) {
    if (v < 1 || v > 1000000000) return ;
    if (*lower_bound(p+1, p+n+2, v) == v) return ;
    values[++nValue] = v;
}

set< pair<long long,int> > event;
set< pair<int,int> > q;

long long check(int pr) {
    a[id].p = pr;
    event.clear();
    q.clear();

    FOR(i,1,n)
        event.insert(MP(a[i].t, i));

    memset(progress, 0, sizeof progress);

    int current = -1;
    long long startTime = 0;
    while (!event.empty()) {
        pair<long long,int> cur = *event.begin(); event.erase(event.begin());

        long long t = cur.F;
        int u = cur.S;

        // cout << "time = " << t << " --> add: " << u << endl;

        if (!q.empty()) {
            pair<int,int> now = *q.begin();
            int v = now.S;

            long long curStart = max(startTime, (ll)a[v].t);
            long long can = min(t - curStart, (ll) a[v].s - progress[v]);

            startTime = t;

            // cout << "do " << v << " : " << can << '/' << a[v].s << endl;

            progress[v] += can;
            if (progress[v] == a[v].s) {
                finish[v] = startTime;
                q.erase(q.begin());
            }
        }

        if (cur.S > 0)
            q.insert(MP(-a[u].p, u));

        if (!q.empty()) {
            u = q.begin()->S;
            event.insert(MP(startTime + a[u].s - progress[u], 0));
        }
    }

    // DEBUG(pr);
    // PR(finish, n);

    return finish[id];
}

int main() {
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
    while (scanf("%d", &n) == 1) {
        FOR(i,1,n) scanf("%d%d%d", &a[i].t, &a[i].s, &a[i].p);
        cin >> T;

        FOR(i,1,n) p[i] = a[i].p;
        sort(p+1, p+n+1);
        p[n+1] = 1000111000;

        nValue = 0;
        FOR(i,1,n) if (a[i].p >= 0) {
            add(a[i].p-1);
            add(a[i].p+1);
        }
        sort(values + 1, values + nValue + 1);
        // PR(values, nValue);

        id = -1;
        FOR(i,1,n) if (a[i].p < 0) id = i;

        int l = 1, r = nValue, res = r;
        while (l <= r) {
            int mid = (l + r) >> 1;
            long long t = check(values[mid]);
            if (t >= T) {
                res = mid;
                l = mid + 1;
            }
            else r = mid - 1;
        }

        // FOR(t,1,nValue) {
        //     DEBUG(check(values[t]));
        // }

        check(values[res]);
        printf("%d\n", values[res]);
        FOR(i,1,n)
            printf("%I64d ", finish[i]);
        puts("");
    }
    return 0;
}
