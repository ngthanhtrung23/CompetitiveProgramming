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

struct Frame {
    int x[7];
} a[1000111];
int n;

vector< Frame > typ[3];

#define NO { puts("NO"); continue; }
#define YES { puts("YES"); continue; }
const int oo = 1000111000;

bool good(vector< pair<int,int> > a, vector< pair<int,int> > b) {
    int mina2 = oo, maxa1 = -oo;
    REP(i,a.size()) {
        mina2 = min(mina2, a[i].second);
        maxa1 = max(maxa1, a[i].first);
    }

    REP(i,b.size()) {
        if (mina2 < b[i].first) return false;
        if (maxa1 > b[i].second) return false;
    }
    return true;
}

bool check(int t1, int t2) {
    int minxt1 = oo, maxxt1 = -oo, minxt2 = oo, maxxt2 = -oo;
    REP(i,typ[t1].size()) {
        minxt1 = min(minxt1, typ[t1][i].x[t1]);
        maxxt1 = max(maxxt1, typ[t1][i].x[t1]);
    }
    REP(i,typ[t2].size()) {
        minxt2 = min(minxt2, typ[t2][i].x[t2]);
        maxxt2 = max(maxxt2, typ[t2][i].x[t2]);
    }

    REP(i,typ[t1].size()) {
        if (!(typ[t1][i].x[t2] < minxt2 && typ[t1][i].x[t2+3] > maxxt2)) return false;
    }
    REP(i,typ[t2].size()) {
        if (!(typ[t2][i].x[t1] < minxt1 && typ[t2][i].x[t1+3] > maxxt1)) return false;
    }

    vector< pair<int,int> > a, b;
    REP(i,typ[t1].size())
        a.push_back(make_pair(typ[t1][i].x[3-t1-t2], typ[t1][i].x[6-t1-t2]));
    REP(i,typ[t2].size())
        b.push_back(make_pair(typ[t2][i].x[3-t1-t2], typ[t2][i].x[6-t1-t2]));

    if (good(a, b) && good(b, a)) return true;
    return false;
}

bool check3() {
    if (check(0, 1) && check(0, 2)) return true;
    if (check(1, 0) && check(1, 2)) return true;
    if (check(2, 0) && check(2, 1)) return true;
    return false;
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        cin >> n;
        REP(t,3) typ[t].clear();

        FOR(i,1,n) {
            REP(t,6) cin >> a[i].x[t];
            REP(t,3) {
                if (a[i].x[t] > a[i].x[t+3]) {
                    swap(a[i].x[t], a[i].x[t+3]);
                }
            }
            REP(t,3)
                if (a[i].x[t] == a[i].x[t+3])
                    typ[t].push_back(a[i]);
        }

        int nEmpty = 0;
        REP(t,3) if (typ[t].empty()) ++nEmpty;
        if (nEmpty == 2) NO;

        if (nEmpty == 0) {
            if (check3()) YES else NO;
        }

        if (typ[0].empty()) if (check(1, 2)) YES else NO;
        if (typ[1].empty()) if (check(0, 2)) YES else NO;
        if (typ[2].empty()) if (check(0, 1)) YES else NO;
    }
    return 0;
}
