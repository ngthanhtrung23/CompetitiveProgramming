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

const int MN = 100111;
pair<int,int> a[MN];

bool cmp(const pair<int,int> &x, const pair<int,int> &y) {
    int tx = abs(x.first) + abs(x.second);
    int ty = abs(y.first) + abs(y.second);
    return tx < ty;
}

int main() {
    ios :: sync_with_stdio(false);
    int n;
    while (cin >> n) {
        FOR(i,1,n) {
            cin >> a[i].first >> a[i].second;
        }
        sort(a+1, a+n+1, cmp);
        int res = 0;
        FOR(i,1,n) {
            if (a[i].first) res += 2;
            if (a[i].second) res += 2;
            res += 2;
        }
        printf("%d\n", res);
        FOR(i,1,n) {
            int x = a[i].first, y = a[i].second;
            if (x > 0) printf("1 %d R\n", x);
            if (x < 0) printf("1 %d L\n", -x);
            if (y > 0) printf("1 %d U\n", y);
            if (y < 0) printf("1 %d D\n", -y);
            puts("2");
            if (x > 0) printf("1 %d L\n", x);
            if (x < 0) printf("1 %d R\n", -x);
            if (y > 0) printf("1 %d D\n", y);
            if (y < 0) printf("1 %d U\n", -y);
            puts("3");
        }
    }
    return 0;
}
