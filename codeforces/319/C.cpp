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
int n, top;
long long a[MN], b[MN], f[MN];
pair<long long, long long> x[MN];
double pos[MN];

void addLine(long long f3, long long b3) {
    while (top > 1) {
        long long f1 = x[top-1].first, b1 = x[top-1].second;
        long long f2 = x[top].first, b2 = x[top].second;

        if ((f3-f1) / (b1-b3) <= (f2-f1) / (b1-b2)) --top;
        else break;
    }
    pos[top+1] = (f3 - x[top].first) / (double) (x[top].second - b3);
    x[++top] = make_pair(f3, b3);
}

long long get(long long a) {
    pos[top+1] = 1e50;
    int id = upper_bound(pos+1, pos+top+2, a) - pos - 1;
    return x[id].first + x[id].second * a;
}

int main() {
    while (cin >> n) {
        FOR(i,1,n) cin >> a[i];
        FOR(i,1,n) cin >> b[i];
        f[1] = 0;
        x[top = 1] = make_pair(f[1], b[1]);
        pos[1] = 0;

        FOR(i,2,n) {
            // FOR(k,1,top) cout << pos[k] << "  " << x[k].first << ' ' << x[k].second << endl;
            f[i] = get(a[i]);
            addLine(f[i], b[i]);
            // DEBUG(f[i]);
        }

        cout << f[n] << endl;
    }
    return 0;
}
