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

int n, cnt[11];
char a[33][33], b[33][33];

bool good() {
    FOR(i,1,n) FOR(j,1,n)
        if (a[i][j] != a[1][1]) return false;
    return true;
}

int first, last, qu[511], qv[511];
const int di[] = {-1,1,0,0};
const int dj[] = {0,0,-1,1};
bool visited[33][33];

int getCur() {
    first = last = 1; qu[1] = 1; qv[1] = 1;
    memset(visited, false, sizeof visited);
    visited[1][1] = true;
    while (first <= last) {
        int u = qu[first], v = qv[first]; ++first;
        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu < 1 || uu > n || vv < 1 || vv > n) continue;
            if (a[uu][vv] != a[1][1] || visited[uu][vv]) continue;

            visited[uu][vv] = true;
            ++last;
            qu[last] = uu; qv[last] = vv;
        }
    }
    return last;
}

int first2, last2, qu2[511], qv2[511];

int modify(char c) {
    FOR(i,1,n) FOR(j,1,n) b[i][j] = a[i][j];
    FOR(i,1,last) {
        b[qu[i]][qv[i]] = c;
    }

    memset(visited, false, sizeof visited);
    first2 = last2 = 1;
    qu2[1] = 1; qv2[1] = 1;
    visited[1][1] = true;

    while (first2 <= last2) {
        int u = qu2[first2], v = qv2[first2]; ++first2;
        REP(dir,4) {
            int uu = u + di[dir], vv = v + dj[dir];
            if (uu < 1 || uu > n || vv < 1 || vv > n) continue;
            if (b[uu][vv] != b[1][1] || visited[uu][vv]) continue;

            visited[uu][vv] = true;
            ++last2;
            qu2[last2] = uu; qv2[last2] = vv;
        }
    }
    return last2;
}

void applyModify(char c) {
    modify(c);
    FOR(i,1,last2) {
        a[qu2[i]][qv2[i]] = c;
    }
}

int main() {
    ios :: sync_with_stdio(false);
    int ntest; cin >> ntest;
    while (ntest--) {
        memset(cnt, 0, sizeof cnt);
        cin >> n;
        FOR(i,1,n) FOR(j,1,n) {
            cin >> a[i][j];
        }
        while (!good()) {
            int cur = getCur(), best = 0;
            char save;
            FOR(c,'1','6') {
                int next = modify(c);
                if (next > best) {
                    best = next;
                    save = c;
                }
            }
            applyModify(save);
            ++cnt[save - '0'];
        }
        int sum = 0;
        FOR(c,'1','6') sum += cnt[c-'0'];
        cout << sum << "\n";
        FOR(c,'1','6') cout << cnt[c-'0'] << ' ';
        cout << "\n";
    }
    return 0;
}
